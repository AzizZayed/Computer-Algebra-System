//
// Created by Abd-El-Aziz Zayed on 2022-12-31.
//

#ifndef COMPUTERALGEBRASYSTEM_SURFACE_H
#define COMPUTERALGEBRASYSTEM_SURFACE_H

#include <fstream>
#include <string>

#include "Grid.h"
#include "cas/latex/LatexRenderer.h"
#include "cas/plot/Function.h"

#import <Metal/Metal.h>
#import <MetalKit/MetalKit.h>
#import <QuartzCore/QuartzCore.h>

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

class Surface {
public:
    struct Plot {
        cas::Function* function{};
        Texture* texture{};
        Vertex* vertices{};
        id<MTLBuffer> vertexBuffer{};
        size_t bufferSize{};
        // random color with c++11
        float color[4] = {static_cast<float>(rand()) / RAND_MAX,
                          static_cast<float>(rand()) / RAND_MAX,
                          static_cast<float>(rand()) / RAND_MAX, 1.0f};
        bool render = true;
    };

    explicit Surface(id<MTLDevice> device, const std::string& func, const Grid& grid) : func(func), grid(grid) {
        cas::LatexRenderer& latexRenderer = cas::LatexRenderer::getInstance();

        plots[plot].function = new cas::Function(func, (const std::string&) "z", false);
        plots[dx].function = plots[plot].function->simplifiedDerivative('x');
        plots[dy].function = plots[plot].function->simplifiedDerivative('y');

        for (auto& p: plots) {
            if (p.function != nullptr) {
                std::string imagePath = latexRenderer.render(*p.function);
                p.texture = new Texture(device, imagePath);
                p.vertices = new Vertex[grid.vertexCount];
                p.bufferSize = grid.vertexCount * sizeof(Vertex);
                p.vertexBuffer = [device newBufferWithLength:p.bufferSize options:MTLResourceStorageModeShared];
            }
        }
        plots[plot].render = true;
    }

    explicit Surface(id<MTLDevice> device, const char* func, const Grid& grid) : Surface(device, std::string(func), grid) {}

    ~Surface() {
        for (Plot& p: plots) {
            if (p.function != nullptr) {
                delete p.function;
                delete p.texture;
                delete[] p.vertices;
                [p.vertexBuffer release];
            }
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
        for (auto& p: plots) {
            if (p.render && p.function != nullptr) {
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
        cas::VariableMap vars = {{'x', x}, {'y', y}};
        for (uint32_t j = 0; j < grid.WIDTH; j++) {
            for (uint32_t i = 0; i < grid.WIDTH; i++) {
                vars['x'] = x;
                vars['y'] = y;
                double z = p.function->evaluate(vars);

                auto xf = static_cast<float>(x);
                auto yf = static_cast<float>(y);
                auto zf = static_cast<float>(z);
                p.vertices[index].position = vector3(xf, yf, zf);
                p.vertices[index++].color = vector4(p.color[0], p.color[1], p.color[2], p.color[3]);

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

#endif//COMPUTERALGEBRASYSTEM_SURFACE_H
