#include <memory>

#include "Grid.h"
#include "Surface.h"
#include "Window.h"

#import <Metal/Metal.h>
#import <MetalKit/MetalKit.h>
#import <QuartzCore/QuartzCore.h>

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
    id<MTLLibrary> library = getLibrary(device);
    id<MTLFunction> vertexFunction = [library newFunctionWithName:@"vertexMain"];// struct with both functions
    id<MTLFunction> fragmentFunction = [library newFunctionWithName:@"fragmentMain"];
    MTLVertexDescriptor* vertexDescriptor = getVertexDescriptor();
    MTLRenderPipelineDescriptor* pipelineStateDescriptor = getRenderPipelineDescriptor(vertexFunction, fragmentFunction, vertexDescriptor);
    id<MTLRenderPipelineState> pipelineState = getRenderPipelineState(device, pipelineStateDescriptor);
    MTLDepthStencilDescriptor* depthStencilDescriptor = getDepthStencilDescriptor();
    id<MTLDepthStencilState> depthStencilState = [device newDepthStencilStateWithDescriptor:depthStencilDescriptor];

    // ==================== Setup ====================

    Grid grid;
    Window window("Computer Algebra System", device, grid);
    std::vector<std::shared_ptr<Surface>> surfaces;
    surfaces.push_back(std::make_shared<Surface>(device, "abs(x * y)", grid));
    surfaces.push_back(std::make_shared<Surface>(device, "floor(round(ceil(x + y)))", grid));


    WorldView worldView = {math::perspective(M_PI / 3, window.bufferAspect, 0.1f, 1000.0f)};

    // ==================== Main Loop ====================

    size_t nFunctions = surfaces.size();
    while (!window.shouldClose()) {
        bool frameBufferSizeChanged = window.update();

        if (frameBufferSizeChanged) {
            window.layer.drawableSize = CGSizeMake(window.bufferWidth, window.bufferHeight);
            worldView.perspective = math::perspective(M_PI / 3, window.bufferAspect, 0.1f, 1000.0f);
        }

        @autoreleasepool {
            // ==================== PREP FRAME ====================
            id<CAMetalDrawable> drawable = [window.layer nextDrawable];
            id<MTLCommandBuffer> commandBuffer = [commandQueue commandBuffer];
            MTLRenderPassDescriptor* renderPassDescriptor = getRenderPassDescriptor(drawable);
            id<MTLRenderCommandEncoder> renderCommandEncoder = [commandBuffer renderCommandEncoderWithDescriptor:renderPassDescriptor];
            window.prepareImGuiFrame(renderPassDescriptor);

            // ==================== INPUT ====================
            const ImVec2& drag = window.getMouseDragDelta();
            const ImVec2& scroll = window.getMouseScrollDelta();

            // ==================== UPDATE ====================
            ImGuiIO& io = ImGui::GetIO();

            bool firstFrame = window.frames == 1;
            bool gridChanged = drag.x != 0 || drag.y != 0 || scroll.x != 0 || scroll.y != 0;
            bool functionsChanged = nFunctions != surfaces.size();
            bool mouseDown = io.MouseDown[0] || io.MouseDown[1] || io.MouseDown[2];

            grid.rotate(drag.y * window.deltaTime, drag.x * window.deltaTime);
            grid.scale(scroll.y * window.deltaTime, 0.5);
            grid.raise(scroll.x * window.deltaTime);

            for (auto& surface: surfaces) {
                surface->update();
            }

            //            nFunctions = surfaces.size();
            Transform transform = grid.transform();

            // ==================== RENDER ====================

            [renderCommandEncoder setRenderPipelineState:pipelineState];
            [renderCommandEncoder setDepthStencilState:depthStencilState];
            [renderCommandEncoder setVertexBytes:&worldView length:sizeof(WorldView) atIndex:15];
            [renderCommandEncoder setVertexBytes:&transform length:sizeof(Transform) atIndex:16];
            [renderCommandEncoder setTriangleFillMode:MTLTriangleFillModeLines];

            for (auto& surface: surfaces) {
                for (Surface::Plot& p: surface->plots) {
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
            }

            [renderCommandEncoder pushDebugGroup:@"GuiRenderer"];
            [renderCommandEncoder setTriangleFillMode:MTLTriangleFillModeFill];

            window.drawImGuiSideBar(surfaces);
            window.drawImGuiTimeWindow();
            window.drawImGuiFrame(commandBuffer, renderCommandEncoder);

            [renderCommandEncoder popDebugGroup];
            [renderCommandEncoder endEncoding];
            [commandBuffer presentDrawable:drawable];
            [commandBuffer commit];
        }
    }

    cas::LatexRenderer::getInstance().cleanup();

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

    return 0;
}
