//
// Created by Abd-El-Aziz Zayed on 2023-01-02.
//

#ifndef COMPUTERALGEBRASYSTEM_MODEL_H
#define COMPUTERALGEBRASYSTEM_MODEL_H

#include <fstream>
#include <string>

#import <Metal/Metal.h>
#import <MetalKit/MetalKit.h>
#import <QuartzCore/QuartzCore.h>

class Model {
public:
    explicit Model(id<MTLDevice> device, const Vertex vertices[], size_t vc, const uint16_t indices[], size_t ic)
        : vertexBufferSize(vc * sizeof(Vertex)), indexBufferSize(ic * sizeof(uint16_t)), vertexCount(vc), indexCount(ic) {
        vertexBuffer = [device newBufferWithBytes:vertices length:this->vertexBufferSize options:MTLResourceStorageModeShared];
        indexBuffer = [device newBufferWithBytes:indices length:this->indexBufferSize options:MTLResourceStorageModeShared];
    }

public:
    size_t vertexBufferSize;
    size_t indexBufferSize;
    id<MTLBuffer> vertexBuffer;
    id<MTLBuffer> indexBuffer;
    size_t vertexCount;
    size_t indexCount;
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

#endif//COMPUTERALGEBRASYSTEM_MODEL_H
