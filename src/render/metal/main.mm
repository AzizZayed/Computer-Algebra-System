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
    explicit Window(const char* title, id<MTLDevice> device) : title(title) {
        glfwSetErrorCallback([](int error, const char* description) {
            fprintf(stderr, "Glfw Error %d: %s\n", error, description);
        });

        if (!glfwInit()) {
            glfwTerminate();
            fprintf(stderr, "Failed to initialize GLFW\n");
            exit(EXIT_FAILURE);
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

        const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

        width = mode->width;
        height = mode->height;

        window = glfwCreateWindow(width, height, title, nullptr, nullptr);
        if (window == nullptr) {
            glfwTerminate();
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
    const char* title;
    GLFWwindow* window{};
    NSWindow* cocoaWindow;
    CAMetalLayer* layer;
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
    explicit GuiRenderer(GLFWwindow* window, id<MTLDevice> device, int width, int height) : width(width), height(height) {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
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

    void prepareFrame(id<MTLRenderCommandEncoder> encoder, MTLRenderPassDescriptor* descriptor) {
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

    void renderTexture(id<MTLTexture> texture) {
        ImGui::Image((__bridge ImTextureID) texture, ImVec2(texture.width, texture.height), ImVec2(0, 1), ImVec2(1, 0));
    }

    void renderFrame(id<MTLCommandBuffer> commandBuffer, id<MTLRenderCommandEncoder> encoder) {
        ImGui::Render();
        ImGui_ImplMetal_RenderDrawData(ImGui::GetDrawData(), commandBuffer, encoder);

        [encoder popDebugGroup];
    }

    void renderTime(double deltaTime, int frames, double timeSinceStart) const {
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

    ImVec2 getMouseDragDelta() const {
        ImGuiIO& io = ImGui::GetIO();
        if (io.MouseDown[ImGuiMouseButton_Left]) {
            return io.MouseDelta;
        }
        return {0, 0};
    }

public:
    bool show_demo_window = true;
    int width;
    int height;
};

class Texture {
public:
    explicit Texture(id<MTLDevice> device, const std::string& imagePath) : path(imagePath) {
        getImageSize(imagePath);

        CGContext* context = CGBitmapContextCreate(nil, width, height, bitsPerComponent,
                                                   width * sizeof(float),
                                                   CGColorSpaceCreateDeviceRGB(),
                                                   kCGImageAlphaPremultipliedLast);

        CGAffineTransform flipVertical = CGAffineTransformMake(1, 0, 0, -1, 0, height);
        CGContextConcatCTM(context, flipVertical);

        CGImageSourceRef imageSourceCreateWithUrl = CGImageSourceCreateWithURL(
                (CFURLRef) [NSURL fileURLWithPath:[NSString stringWithUTF8String:path.c_str()]], nil);
        CGImage* image = CGImageSourceCreateImageAtIndex(imageSourceCreateWithUrl, 0, nil);
        CGContextDrawImage(context, CGRectMake(0, 0, width, height), image);

        MTLTextureDescriptor* textureDescriptor = [[MTLTextureDescriptor alloc] init];
        textureDescriptor.pixelFormat = MTLPixelFormatBGRA8Unorm;
        textureDescriptor.width = width;
        textureDescriptor.height = height;

        metalTexture = [device newTextureWithDescriptor:textureDescriptor];
        MTLRegion region = MTLRegionMake2D(0, 0, width, height);
        [metalTexture replaceRegion:region mipmapLevel:0 withBytes:CGBitmapContextGetData(context) bytesPerRow:width * 4];
        if (metalTexture == nil) {
            NSLog(@"Failed to create texture");
            exit(EXIT_FAILURE);
        }
    }

    ~Texture() {
        [metalTexture release];
    }

    void getImageSize(const std::string& imagePath) {
        std::ifstream in(imagePath);
        in.seekg(16);
        in.read((char*) &width, 4);
        in.read((char*) &height, 4);

        width = ntohl(width);
        height = ntohl(height);
    }

public:
    const std::string path;
    id<MTLTexture> metalTexture;
    size_t width{};
    size_t height{};
    size_t bitsPerComponent{8};
};

struct Grid {
    const uint32_t RESOLUTION = 100;
    const uint32_t WIDTH = RESOLUTION + 1;
    const uint32_t indexCount = RESOLUTION * RESOLUTION * 6;
    const uint32_t vertexCount = WIDTH * WIDTH;

    double xMin = -1.0;
    double xMax = 1.0;
    double yMin = -1.0;
    double yMax = 1.0;

    double xRotation = 0.0;
    double zRotation = 0.0;

    double xLength() const {
        return xMax - xMin;
    }

    double yLength() const {
        return yMax - yMin;
    }

    double xStep() const {
        return xLength() / RESOLUTION;
    }

    double yStep() const {
        return yLength() / RESOLUTION;
    }

    void scale(double factor = 0.01) {
        xMin -= factor;
        yMin -= factor;
        xMax += factor;
        yMax += factor;
    }

    void rotate(double x, double z, double damping = 1.0) {
        xRotation += x * damping;
        zRotation += z * damping;
    }

    Transform transform() const {
        double z = -4.0;
        double damp = 0.5;
        double scale = 3.0f;

        return {
                math::translate(0, 0, z),
                math::xRotate(-xRotation * damp) * math::zRotate(-zRotation * damp),
                math::scale(scale / xLength(), scale / yLength(), scale / yLength())};
    }
};

class Surface {
public:

    struct Plot {
        cas::Function* function{};
        Texture* texture{};
        Vertex* vertices{};
        id<MTLBuffer> vertexBuffer{};
        size_t bufferSize{};
        simd::float4 color = vector4(1.0f, 1.0f, 0.0f, 1.0f);
        bool render = true;

        ~Plot() {
            delete function;
            delete texture;
            delete[] vertices;
            [vertexBuffer release];
        }
    };

    explicit Surface(id<MTLDevice> device, const std::string& func, const Grid& grid) : func(func), grid(grid)
    {
        cas::LatexRenderer& latexRenderer = cas::LatexRenderer::getInstance();

        plots[plot].function = new cas::Function(func, (const std::string&) "z");
        plots[dx].function = plots[plot].function->derivative('x'); // TODO simplify
        plots[dy].function = plots[plot].function->derivative('y'); // TODO simplify

        for (auto& p : plots) {
            std::string imagePath = latexRenderer.render(*p.function);
            p.texture = new Texture(device, imagePath);
            p.vertices = new Vertex[grid.vertexCount];
            p.bufferSize = grid.vertexCount * sizeof(Vertex);
            p.vertexBuffer = [device newBufferWithLength:p.bufferSize options:MTLResourceStorageModeShared];
        }
    }

    static id<MTLBuffer> getIndexBuffer(id<MTLDevice> device, const Grid& grid) {
        static uint32_t* indices;
        static id<MTLBuffer> indexBuffer;

        if (indices == nullptr && indexBuffer == nil) {
            indices = new uint32_t[grid.indexCount];

            uint32_t index = 0;
            for (uint32_t j = 0; j < grid.RESOLUTION; j++) {
                for (uint32_t i = 0; i < grid.RESOLUTION; i++) {
                    uint32_t a = j * grid.WIDTH + i;
                    uint32_t b = a + 1;
                    uint32_t c = (j + 1) * grid.WIDTH + i;
                    uint32_t d = c + 1;

                    indices[index++] = a;
                    indices[index++] = b;
                    indices[index++] = c;

                    indices[index++] = b;
                    indices[index++] = c;
                    indices[index++] = d;
                }
            }

            indexBuffer = [device newBufferWithBytes:indices
                                              length:grid.indexCount * sizeof(uint32_t)
                                             options:MTLResourceStorageModeShared];
            printf("Index buffer created.");
        }

        return indexBuffer;
    }

    void update() {
        for (auto& p : plots) {
            if (p.render) {
                updateVertices(p);
            }
        }
    }

    void updateVertices(Plot& p) {
        const double _dx = grid.xStep();
        const double _dy = grid.yStep();
        double x = grid.xMin;
        double y = grid.yMin;

        uint32_t index = 0;
        cas::VarMap vars = {{'x', x}, {'y', y}};
        for (uint32_t j = 0; j < grid.WIDTH; j++) {
            for (uint32_t i = 0; i < grid.WIDTH; i++) {
                vars['x'] = x;
                vars['y'] = y;
                double z = p.function->evaluate(vars);

                auto xf = static_cast<float>(x);
                auto yf = static_cast<float>(y);
                auto zf = static_cast<float>(z);
                p.vertices[index].position = vector3(xf, yf, zf);
                p.vertices[index++].color = p.color;

                x += _dx;
            }
            y += _dy;
            x = grid.xMin;
        }

        memcpy(p.vertexBuffer.contents, p.vertices, p.bufferSize);
    }

public:
    const std::string func;
    const Grid& grid;
    Plot plots[3];
    size_t plot = 0, dx = 1, dy = 2;
};


id<MTLLibrary> getLibrary(id<MTLDevice> device) {
    NSError* error = nil;
    NSString* shaderSrc = [NSString stringWithContentsOfFile:@"../src/render/metal/shader.metal" encoding:NSUTF8StringEncoding error:&error];
    if (error) {// The path to the shader file is with respect to the build directory
        NSLog(@"Error loading shader.metal: %@", error);
        exit(EXIT_FAILURE);
    }

    id<MTLLibrary> library = [device newLibraryWithSource:shaderSrc options:nil error:&error];
    if (error) {
        NSLog(@"MTL Library Error: %@", error);
        exit(EXIT_FAILURE);
    }
    return library;
}

MTLVertexDescriptor* getVertexDescriptor() {
    MTLVertexDescriptor* vertexDescriptor = [MTLVertexDescriptor new];
    vertexDescriptor.attributes[0].format = MTLVertexFormatFloat3;// position
    vertexDescriptor.attributes[0].offset = 0;
    vertexDescriptor.attributes[0].bufferIndex = 0;
    vertexDescriptor.attributes[1].format = MTLVertexFormatFloat4;// color
    vertexDescriptor.attributes[1].offset = sizeof(simd::float3);
    vertexDescriptor.attributes[1].bufferIndex = 0;
    vertexDescriptor.layouts[0].stride = sizeof(Vertex);
    return vertexDescriptor;
}

MTLRenderPipelineDescriptor* getRenderPipelineDescriptor(id<MTLFunction> vertexFunction, id<MTLFunction> fragmentFunction, MTLVertexDescriptor* vertexDescriptor) {
    MTLRenderPipelineDescriptor* pipelineStateDescriptor = [[MTLRenderPipelineDescriptor alloc] init];
    pipelineStateDescriptor.vertexFunction = vertexFunction;
    pipelineStateDescriptor.fragmentFunction = fragmentFunction;
    pipelineStateDescriptor.colorAttachments[0].pixelFormat = MTLPixelFormatBGRA8Unorm_sRGB;
    pipelineStateDescriptor.vertexDescriptor = vertexDescriptor;
    return pipelineStateDescriptor;
}

id<MTLRenderPipelineState> getRenderPipelineState(id<MTLDevice> device, MTLRenderPipelineDescriptor* pipelineStateDescriptor) {
    NSError* error = nil;
    id<MTLRenderPipelineState> pipelineState = [device newRenderPipelineStateWithDescriptor:pipelineStateDescriptor error:&error];
    if (error) {
        NSLog(@"Pipeline State Error: %@", error);
        exit(EXIT_FAILURE);
    }
    return pipelineState;
}

MTLDepthStencilDescriptor* getDepthStencilDescriptor() {
    MTLDepthStencilDescriptor* depthStencilDescriptor = [MTLDepthStencilDescriptor new];
    depthStencilDescriptor.depthCompareFunction = MTLCompareFunctionLess;
    depthStencilDescriptor.depthWriteEnabled = YES;
    return depthStencilDescriptor;
}

MTLRenderPassDescriptor* getRenderPassDescriptor(id<CAMetalDrawable> drawable) {
    MTLRenderPassDescriptor* renderPassDescriptor = [MTLRenderPassDescriptor renderPassDescriptor];
    renderPassDescriptor.colorAttachments[0].clearColor = MTLClearColorMake(0, 0, 0, 1);
    renderPassDescriptor.colorAttachments[0].texture = drawable.texture;
    renderPassDescriptor.colorAttachments[0].loadAction = MTLLoadActionClear;
    renderPassDescriptor.colorAttachments[0].storeAction = MTLStoreActionStore;
    return renderPassDescriptor;
}

int main() {
    // Renderer Setup
    id<MTLDevice> device = MTLCreateSystemDefaultDevice();
    id<MTLCommandQueue> commandQueue = [device newCommandQueue];

    Grid grid;
    Window window("Computer Algebra System", device);
    GuiRenderer guiRenderer(window.window, device, window.width, window.height);
    Surface surface(device, (const std::string&) "sin(x*y^2)", grid);

    // Renderer - load shaders and build render pipeline state
    id<MTLLibrary> library = getLibrary(device);
    id<MTLFunction> vertexFunction = [library newFunctionWithName:@"vertexMain"];// struct with both functions
    id<MTLFunction> fragmentFunction = [library newFunctionWithName:@"fragmentMain"];
    MTLVertexDescriptor* vertexDescriptor = getVertexDescriptor();
    MTLRenderPipelineDescriptor* pipelineStateDescriptor = getRenderPipelineDescriptor(vertexFunction, fragmentFunction, vertexDescriptor);
    id<MTLRenderPipelineState> pipelineState = getRenderPipelineState(device, pipelineStateDescriptor);

    // Depth stencil state
    MTLDepthStencilDescriptor* depthStencilDescriptor = getDepthStencilDescriptor();
    id<MTLDepthStencilState> depthStencilState = [device newDepthStencilStateWithDescriptor:depthStencilDescriptor];


    // ==================== Setup ====================

    window.layer.drawableSize = CGSizeMake(window.bufferWidth, window.bufferHeight);
    WorldView worldView = {
            math::perspective(M_PI / 3, window.bufferAspect, 0.1f, 1000.0f)};

    // ==================== Main Loop ====================

    while (!window.shouldClose()) {
        window.update();

        surface.update();

        if (grid.xMax < 4) {
            grid.scale(0.01);
        }

        const ImVec2& vec2 = guiRenderer.getMouseDragDelta();
        grid.rotate(vec2.y * window.deltaTime, vec2.x * window.deltaTime);
        Transform transform = grid.transform();

        // ==================== Render ====================

        @autoreleasepool {
            id<CAMetalDrawable> drawable = [window.layer nextDrawable];
            id<MTLCommandBuffer> commandBuffer = [commandQueue commandBuffer];
            MTLRenderPassDescriptor* renderPassDescriptor = getRenderPassDescriptor(drawable);

            // Renderer draw
            id<MTLRenderCommandEncoder> renderCommandEncoder = [commandBuffer renderCommandEncoderWithDescriptor:renderPassDescriptor];

            [renderCommandEncoder setRenderPipelineState:pipelineState];
            [renderCommandEncoder setDepthStencilState:depthStencilState];
            [renderCommandEncoder setVertexBytes:&worldView length:sizeof(WorldView) atIndex:15];
            [renderCommandEncoder setVertexBytes:&transform length:sizeof(Transform) atIndex:16];
            [renderCommandEncoder setTriangleFillMode:MTLTriangleFillModeLines];

            for (auto& p : surface.plots) {
                if (p.render) {
                    [renderCommandEncoder setVertexBuffer:p.vertexBuffer offset:0 atIndex:0];
                    [renderCommandEncoder
                            drawIndexedPrimitives:MTLPrimitiveTypeTriangle
                                       indexCount:grid.indexCount
                                        indexType:MTLIndexTypeUInt32
                                      indexBuffer:Surface::getIndexBuffer(device, grid)
                                indexBufferOffset:0];
                }
            }

            guiRenderer.prepareFrame(renderCommandEncoder, renderPassDescriptor);
            guiRenderer.renderDemoWindow();
            for (auto& plot : surface.plots) {
                guiRenderer.renderTexture(plot.texture->metalTexture);
            }
            guiRenderer.renderTime(window.deltaTime, window.frames, window.getTimeSinceRenderStart());
            guiRenderer.renderFrame(commandBuffer, renderCommandEncoder);

            [renderCommandEncoder endEncoding];
            [commandBuffer presentDrawable:drawable];
            [commandBuffer commit];
        }
    }

    [device release];
    [commandQueue release];
    [library release];
    [vertexFunction release];
    [fragmentFunction release];
    [vertexDescriptor release];
    [pipelineStateDescriptor release];
    [pipelineState release];
    [depthStencilDescriptor release];
    [depthStencilState release];

    cas::LatexRenderer::getInstance().cleanup();

    return 0;
}
