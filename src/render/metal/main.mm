#include <fstream>

#define GLFW_INCLUDE_NONE
#define GLFW_EXPOSE_NATIVE_COCOA

#include "GLFW/glfw3.h"
#include "GLFW/glfw3native.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_metal.h"

#import "cas/latex/LatexRenderer.h"
#import "cas/plot/Function.h"
#include "metal_math.h"
#include "metal_types.h"
#import <Metal/Metal.h>
#import <MetalKit/MetalKit.h>

class Window {
public:
    explicit Window(const char *title, id <MTLDevice> device) : title(title) {
        glfwSetErrorCallback([](int error, const char *description) {
            fprintf(stderr, "Glfw Error %d: %s\n", error, description);
        });

        if (!glfwInit()) {
            fprintf(stderr, "Failed to initialize GLFW\n");
            exit(EXIT_FAILURE);
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

        const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

        width = mode->width;
        height = mode->height;

        window = glfwCreateWindow(width, height, title, nullptr, nullptr);
        if (window == nullptr) {
            fprintf(stderr, "Failed to create window\n");
            exit(EXIT_FAILURE);
        }

        glfwGetFramebufferSize(window, &bufferWidth, &bufferHeight);
        bufferAspect = (float) bufferWidth / (float) bufferHeight;
        lastFrameTime = glfwGetTime();

        cocoaWindow = glfwGetCocoaWindow(window);
        [cocoaWindow setAcceptsMouseMovedEvents:YES];
        [cocoaWindow setCollectionBehavior:NSWindowCollectionBehaviorFullScreenPrimary];

        layer = [CAMetalLayer layer];
        layer.device = device;
        layer.pixelFormat = MTLPixelFormatBGRA8Unorm;
        cocoaWindow.contentView.layer = layer;
        cocoaWindow.contentView.wantsLayer = YES;
    }

    ~Window() {
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    bool shouldClose() const {
        return glfwWindowShouldClose(window);
    }

    void update() {
        if (renderStartTime == 0.0) {
            renderStartTime = glfwGetTime();
        }

        frames++;
        double currentTime = glfwGetTime();
        deltaTime = currentTime - lastFrameTime;
        lastFrameTime = currentTime;
        glfwPollEvents();
    }

    double getTimeSinceRenderStart() const {
        return glfwGetTime() - renderStartTime;
    }

public:
    const char *title;
    GLFWwindow *window{};
    NSWindow *cocoaWindow;
    CAMetalLayer *layer;
    double deltaTime{};
    double lastFrameTime{};
    int frames{};
    double renderStartTime{};
    int width{};
    int height{};
    int bufferWidth{};
    int bufferHeight{};
    float bufferAspect;
};

class GuiRenderer {
public:
    explicit GuiRenderer(GLFWwindow *window, id <MTLDevice> device, int width, int height) : width(width), height(height) {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        (void) io;
        ImGui::StyleColorsDark();

        ImGui_ImplGlfw_InitForOther(window, true);
        ImGui_ImplMetal_Init(device);
    }

    ~GuiRenderer() {
        ImGui_ImplMetal_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void prepareFrame(id <MTLRenderCommandEncoder> encoder, MTLRenderPassDescriptor *descriptor) {
        [encoder pushDebugGroup:@"GuiRenderer"];
        [encoder setTriangleFillMode:MTLTriangleFillModeFill];

        // ImGui draw
        ImGui_ImplMetal_NewFrame(descriptor);
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void renderDemoWindow() {
        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);
    }

    void renderTime(double deltaTime) {
        ImGui::Text("dt: %f ms", deltaTime * 1000.0f);
        ImGui::Text("%f FPS", 1 / deltaTime);
    }

    void renderTexture(id <MTLTexture> texture) {
        ImGui::Image((__bridge ImTextureID) texture, ImVec2(texture.width, texture.height), ImVec2(0, 1), ImVec2(1, 0));
    }

    void renderFrame(id <MTLCommandBuffer> commandBuffer, id <MTLRenderCommandEncoder> encoder) {
        ImGui::Render();
        ImGui_ImplMetal_RenderDrawData(ImGui::GetDrawData(), commandBuffer, encoder);

        [encoder popDebugGroup];
    }

    void renderFPS(double deltaTime, int frames, double timeSinceStart) {
        const ImVec2& size = ImVec2(130, 80);

        ImGui::SetNextWindowPos(ImVec2(width - size.x, 0), ImGuiCond_Always);
        ImGui::SetNextWindowSize(size, ImGuiCond_Always);
        ImGui::Begin("FPS", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings);
        ImGui::Text("dt: %f ms", deltaTime * 1000.0f);
        ImGui::Text("t : %f s", timeSinceStart);
        ImGui::Text("%f FPS", 1 / deltaTime);
        ImGui::Text("%d frames", frames);
        ImGui::End();
    }

public:
    bool show_demo_window = true;
    int width;
    int height;
};

class Model {
public:
    explicit Model(id <MTLDevice> device, const Vertex vertices[], size_t vc, const uint16_t indices[], size_t ic)
            : vertexCount(vc), indexCount(ic) {
        vertexBufferSize = vc * sizeof(Vertex);
        indexBufferSize = ic * sizeof(uint16_t);
        vertexBuffer = [device newBufferWithBytes:vertices length:vertexBufferSize options:MTLResourceStorageModeShared];
        indexBuffer = [device newBufferWithBytes:indices length:indexBufferSize options:MTLResourceStorageModeShared];
    }

public:
    size_t vertexBufferSize;
    size_t indexBufferSize;
    id <MTLBuffer> vertexBuffer;
    id <MTLBuffer> indexBuffer;
    size_t vertexCount;
    size_t indexCount;
};

class Texture {
public:
    explicit Texture(id <MTLDevice> device, const char *path) {
        getImageSize(path);

        CGContext *context = CGBitmapContextCreate(nil, width, height, bitsPerComponent,
                                                   width * sizeof(float),
                                                   CGColorSpaceCreateDeviceRGB(),
                                                   kCGImageAlphaPremultipliedLast);

        CGAffineTransform flipVertical = CGAffineTransformMake(1, 0, 0, -1, 0, height);
        CGContextConcatCTM(context, flipVertical);

        CGImageSourceRef imageSourceCreateWithUrl = CGImageSourceCreateWithURL(
                (CFURLRef) [NSURL fileURLWithPath:[NSString stringWithUTF8String:path]], nil);
        CGImage *image = CGImageSourceCreateImageAtIndex(imageSourceCreateWithUrl, 0, nil);
        CGContextDrawImage(context, CGRectMake(0, 0, width, height), image);

        MTLTextureDescriptor *textureDescriptor = [[MTLTextureDescriptor alloc] init];
        textureDescriptor.pixelFormat = MTLPixelFormatBGRA8Unorm;
        textureDescriptor.width = width;
        textureDescriptor.height = height;

        texture = [device newTextureWithDescriptor:textureDescriptor];
        MTLRegion region = MTLRegionMake2D(0, 0, width, height);
        [texture replaceRegion:region mipmapLevel:0 withBytes:CGBitmapContextGetData(context) bytesPerRow:width * 4];
        if (texture == nil) {
            NSLog(@"Failed to create texture");
        }
    }

    void getImageSize(const char *path) {
        std::ifstream in(path);
        in.seekg(16);
        in.read((char *) &width, 4);
        in.read((char *) &height, 4);

        width = ntohl(width);
        height = ntohl(height);
    }

public:
    id <MTLTexture> texture;
    size_t width{};
    size_t height{};
    size_t bitsPerComponent{8};
};

// Draw complex Model
void drawModel(NSArray<MTKMesh *> *meshes, id <MTLRenderCommandEncoder> renderCommandEncoder) {
    [renderCommandEncoder setTriangleFillMode:MTLTriangleFillModeLines];
    for (MTKMesh *mesh in meshes) {
        for (MTKMeshBuffer *vb in mesh.vertexBuffers) {
            [renderCommandEncoder setVertexBuffer:vb.buffer offset:vb.offset atIndex:0];
            for (MTKSubmesh *subMesh in mesh.submeshes) {
                [renderCommandEncoder
                        drawIndexedPrimitives:subMesh.primitiveType
                                   indexCount:subMesh.indexCount
                                    indexType:subMesh.indexType
                                  indexBuffer:subMesh.indexBuffer.buffer
                            indexBufferOffset:subMesh.indexBuffer.offset];
            }
        }
    }
}


// Draw 3D function
void drawFunction(id <MTLBuffer> vertexBuffer, id <MTLBuffer> indexBuffer, uint32_t indexCount,
                  id <MTLRenderCommandEncoder> renderCommandEncoder) {
//    [renderCommandEncoder setTriangleFillMode:MTLTriangleFillModeFill];
    [renderCommandEncoder setTriangleFillMode:MTLTriangleFillModeLines];
    [renderCommandEncoder setVertexBuffer:vertexBuffer offset:0 atIndex:0];
    [renderCommandEncoder
            drawIndexedPrimitives:MTLPrimitiveTypeTriangle
                       indexCount:indexCount
                        indexType:MTLIndexTypeUInt32
                      indexBuffer:indexBuffer
                indexBufferOffset:0];
}

// Draw simple debug model
void drawDebugModel(const Model &model, id <MTLRenderCommandEncoder> renderCommandEncoder) {
    [renderCommandEncoder setTriangleFillMode:MTLTriangleFillModeLines];
    [renderCommandEncoder setVertexBuffer:model.vertexBuffer offset:0 atIndex:0];
    [renderCommandEncoder
            drawIndexedPrimitives:MTLPrimitiveTypeTriangle
                       indexCount:model.indexCount
                        indexType:MTLIndexTypeUInt16
                      indexBuffer:model.indexBuffer
                indexBufferOffset:0];
}

// Simple 3D function
double f(double x, double y) {
    return sin(x * y*y);
}

int main() {

    // CAS
    cas::Function function{"sin(x*y^2)"};

    cas::LatexRenderer& latexRenderer = cas::LatexRenderer::getInstance();
    std::string imagePath = latexRenderer.render(function, "f");

    // Renderer Setup
    id <MTLDevice> device = MTLCreateSystemDefaultDevice();
    id <MTLCommandQueue> commandQueue = [device newCommandQueue];

    Window window("Computer Algebra System", device);
    GuiRenderer guiRenderer(window.window, device, window.width, window.height);

    Model plane(device, debug::planeVertices, debug::planeVertexCount, debug::planeIndices, debug::planeIndexCount);
    Model cube(device, debug::cubeVertices, debug::cubeVertexCount, debug::cubeIndices, debug::cubeIndexCount);

    Texture texture(device, imagePath.c_str());

    // Renderer - load shaders and build render pipeline state
    NSError *error = nil;
    NSString *shaderSrc = [NSString stringWithContentsOfFile:@"../src/render/metal/shader.metal" encoding:NSUTF8StringEncoding error:&error];
    if (error) { // The path to the shader file is with respect to the build directory
        NSLog(@"Error loading shader.metal: %@", error);
        return EXIT_FAILURE;
    }

    id <MTLLibrary> library = [device newLibraryWithSource:shaderSrc options:nil error:&error];
    if (error) {
        NSLog(@"MTL Library Error: %@", error);
        return EXIT_FAILURE;
    }
    id <MTLFunction> vertexFunction = [library newFunctionWithName:@"vertexMain"]; // struct with both functions
    id <MTLFunction> fragmentFunction = [library newFunctionWithName:@"fragmentMain"];

    MTLVertexDescriptor *vertexDescriptor = [MTLVertexDescriptor new];
    vertexDescriptor.attributes[0].format = MTLVertexFormatFloat3; // position
    vertexDescriptor.attributes[0].offset = 0;
    vertexDescriptor.attributes[0].bufferIndex = 0;
    vertexDescriptor.attributes[1].format = MTLVertexFormatFloat4; // color
    vertexDescriptor.attributes[1].offset = sizeof(simd::float3);
    vertexDescriptor.attributes[1].bufferIndex = 0;
//    vertexDescriptor.attributes[2].format = MTLVertexFormatFloat2; // texture or normal
//    vertexDescriptor.attributes[2].offset = sizeof(simd::float3) * 2;
//    vertexDescriptor.attributes[2].bufferIndex = 0;
    vertexDescriptor.layouts[0].stride = sizeof(Vertex);

    MTLRenderPipelineDescriptor *pipelineStateDescriptor = [[MTLRenderPipelineDescriptor alloc] init];
    pipelineStateDescriptor.vertexFunction = vertexFunction;
    pipelineStateDescriptor.fragmentFunction = fragmentFunction;
    pipelineStateDescriptor.colorAttachments[0].pixelFormat = MTLPixelFormatBGRA8Unorm_sRGB;
    pipelineStateDescriptor.vertexDescriptor = vertexDescriptor;

    id <MTLRenderPipelineState> pipelineState = [device newRenderPipelineStateWithDescriptor:pipelineStateDescriptor error:&error];
    if (error) {
        NSLog(@"Pipeline State Error: %@", error);
        return 1;
    }

    // Depth stencil state
    MTLDepthStencilDescriptor *depthStencilDescriptor = [MTLDepthStencilDescriptor new];
    depthStencilDescriptor.depthCompareFunction = MTLCompareFunctionLess;
    depthStencilDescriptor.depthWriteEnabled = YES;
    id <MTLDepthStencilState> depthStencilState = [device newDepthStencilStateWithDescriptor:depthStencilDescriptor];


    // load model
    MDLVertexDescriptor *mdlVertexDescriptor = MTKModelIOVertexDescriptorFromMetal(vertexDescriptor);
    mdlVertexDescriptor.attributes[0].name = MDLVertexAttributePosition;
    mdlVertexDescriptor.attributes[1].name = MDLVertexAttributeColor;
//    mdlVertexDescriptor.attributes[2].name = MDLVertexAttributeNormal;

    // Load monkey model
    MTKMeshBufferAllocator *meshBufferAllocator = [[MTKMeshBufferAllocator alloc] initWithDevice:device];
    MDLAsset *asset = [[MDLAsset alloc] initWithURL:[NSURL fileURLWithPath:@"../res/models/monkey-normals.obj"] vertexDescriptor:mdlVertexDescriptor bufferAllocator:meshBufferAllocator];
    NSArray<MTKMesh *> *meshes = [MTKMesh newMeshesFromAsset:asset device:device sourceMeshes:nil error:&error];
    if (meshes == nil) {
        NSLog(@"Failed to load model");
        return 1;
    }

    NSLog(@"Loaded model");
    NSLog(@"Meshes: %lu", meshes.count);
    NSLog(@"Vertex count: %lu", meshes[0].vertexCount);
    NSLog(@"Vertex buffer count: %lu", meshes[0].vertexBuffers.count);
    NSLog(@"Sub-Mesh count: %lu", meshes[0].submeshes.count);

    [meshBufferAllocator release];


    // ==================== Setup ====================

    float angle = 0.01f;
    float speed = 0.01f;

    window.layer.drawableSize = CGSizeMake(window.bufferWidth, window.bufferHeight);
    WorldView worldView = {
            math::perspective(M_PI / 3, window.bufferAspect, 0.1f, 1000.0f)
    };

    ImVec2 mouseDragDelta;

    double xRotation = 0.0;
    double zRotation = 0.0;

    const uint32_t MAX_RESOLUTION = 100;
    const uint32_t WIDTH = MAX_RESOLUTION + 1;

    float xMin = -1;
    float yMin = -1;
    float xMax = 1;
    float yMax = 1;

    int k = 0;
    uint32_t indexCount = MAX_RESOLUTION * MAX_RESOLUTION * 6;
    auto *indices = new uint32_t[indexCount]; // dynamic since stack might not be enough
    for (uint32_t j = 0; j < MAX_RESOLUTION; j++) {
        for (uint32_t i = 0; i < MAX_RESOLUTION; i++) {
            uint32_t a = j * WIDTH + i;
            uint32_t b = a + 1;
            uint32_t c = (j + 1) * WIDTH + i;
            uint32_t d = c + 1;

            indices[k++] = a;
            indices[k++] = b;
            indices[k++] = c;

            indices[k++] = b;
            indices[k++] = c;
            indices[k++] = d;
//            printf("%u, %u, %u\n", a, b, c);
//            printf("%u, %u, %u\n", b, c, d);
        }
    }
    id <MTLBuffer> indexBuffer = [device newBufferWithBytes:indices length:indexCount *
                                                                           sizeof(uint32_t) options:MTLResourceStorageModeShared];

    const uint32_t bufferSize = WIDTH * WIDTH;
    auto *vertices = new Vertex[bufferSize]; // dynamic since stack might not be enough

    // ==================== Main Loop ====================

    while (!window.shouldClose()) {
        window.update(); // Window

        const float yLength = yMax - yMin;
        const float xLength = xMax - xMin;
        const float dx = xLength / MAX_RESOLUTION;
        const float dy = yLength / MAX_RESOLUTION;

        float x = xMin;
        float y = yMin;

        k = 0;
        cas::VarMap vars = {{'x', x}, {'y', y}};
        for (uint32_t j = 0; j < WIDTH; j++) {
            for (uint32_t i = 0; i < WIDTH; i++) {
                vars['x'] = x;
                vars['y'] = y;
                float z = function.evaluate(vars);
//                float z = f(x, y);
                vertices[k].position = vector3(x, y, z);
                vertices[k++].color = vector4(0.0f, 1.0f, 0.0f, 1.0f);

                x += dx;
            }
            y += dy;
            x = xMin;
        }


        id <MTLBuffer> vertexBuffer = [device newBufferWithBytes:vertices length:bufferSize *
                                                                                 sizeof(Vertex) options:MTLResourceStorageModeShared];

        if (xMax < 4) {
            xMin -= 0.01;
            yMin -= 0.01;
            xMax += 0.01;
            yMax += 0.01;
//            printf("xMin: %f, yMin: %f, xMax: %f, yMax: %f\n", xMin, yMin, xMax, yMax);
        }

        double deltaTime = window.deltaTime;

        ImGuiIO &io = ImGui::GetIO();
        if (io.MouseDown[ImGuiMouseButton_Left]) {
            mouseDragDelta = io.MouseDelta;
        }

        xRotation += mouseDragDelta.y * deltaTime;
        zRotation += mouseDragDelta.x * deltaTime;

        double damp = 0.5;
        float scale = 3.0f;
        Transform transform = {
                math::translate(0, 0, -4),
                math::xRotate(-xRotation * damp) * math::zRotate(-zRotation * damp),
                math::scale(scale / xLength, scale / yLength, scale / yLength)
        };

        // ==================== Render ====================

        @autoreleasepool {
            id <CAMetalDrawable> drawable = [window.layer nextDrawable];

            id <MTLCommandBuffer> commandBuffer = [commandQueue commandBuffer];
            MTLRenderPassDescriptor *renderPassDescriptor = [MTLRenderPassDescriptor renderPassDescriptor];
            renderPassDescriptor.colorAttachments[0].clearColor = MTLClearColorMake(0, 0, 0, 1);
            renderPassDescriptor.colorAttachments[0].texture = drawable.texture;
            renderPassDescriptor.colorAttachments[0].loadAction = MTLLoadActionClear;
            renderPassDescriptor.colorAttachments[0].storeAction = MTLStoreActionStore;

            // Renderer draw
            id <MTLRenderCommandEncoder> renderCommandEncoder = [commandBuffer renderCommandEncoderWithDescriptor:renderPassDescriptor];

            [renderCommandEncoder setRenderPipelineState:pipelineState];
            [renderCommandEncoder setDepthStencilState:depthStencilState];
            [renderCommandEncoder setVertexBytes:&worldView length:sizeof(WorldView) atIndex:15];
            [renderCommandEncoder setVertexBytes:&transform length:sizeof(Transform) atIndex:16];


            drawFunction(vertexBuffer, indexBuffer, indexCount, renderCommandEncoder);
//            drawModel(meshes, renderCommandEncoder);

//            transform = {
//                    math::translate(0, 0, -4),
//                    math::identity(),
//                    math::scale(1)
//            };
//            [renderCommandEncoder setVertexBytes:&transform length:sizeof(Transform) atIndex:16];
//            drawDebugModel(cube, renderCommandEncoder);

            guiRenderer.prepareFrame(renderCommandEncoder, renderPassDescriptor);
            guiRenderer.renderDemoWindow();
            guiRenderer.renderTexture(texture.texture);
            guiRenderer.renderFPS(window.deltaTime, window.frames, window.getTimeSinceRenderStart());
            guiRenderer.renderFrame(commandBuffer, renderCommandEncoder);

            [renderCommandEncoder endEncoding];
            [commandBuffer presentDrawable:drawable];
            [commandBuffer commit];
        }

        angle += speed;
    }

    latexRenderer.cleanup();

    return 0;
}
