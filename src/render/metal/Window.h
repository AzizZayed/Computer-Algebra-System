//
// Created by Abd-El-Aziz Zayed on 2022-12-31.
//

#ifndef COMPUTERALGEBRASYSTEM_WINDOW_H
#define COMPUTERALGEBRASYSTEM_WINDOW_H

#include <memory>
#include <vector>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_metal.h"

#define GLFW_INCLUDE_NONE
#define GLFW_EXPOSE_NATIVE_COCOA

#include "GLFW/glfw3.h"
#include "GLFW/glfw3native.h"

#import <Metal/Metal.h>
#import <MetalKit/MetalKit.h>
#import <QuartzCore/QuartzCore.h>

#include "Grid.h"
#include "Surface.h"

class Window {
public:
    explicit Window(const char* title, id<MTLDevice> device, const Grid& grid) : device(device), grid(grid), title(title) {
        glfwSetErrorCallback([](int error, const char* description) {
            printf("Glfw Error %d: %s\n", error, description);
        });

        if (!glfwInit()) {
            printf("Failed to initialize GLFW\n");
            exit(EXIT_FAILURE);
        }

        const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

        width = mode->width;
        height = mode->height;

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        window = glfwCreateWindow(width, height, title, nullptr, nullptr);
        if (window == nullptr) {
            printf("Failed to create window\n");
            exit(EXIT_FAILURE);
        }

        glfwGetWindowSize(window, &width, &height);
        glfwGetFramebufferSize(window, &bufferWidth, &bufferHeight);
        glfwGetWindowContentScale(window, &scaleX, &scaleY);

        bufferAspect = (float) bufferWidth / (float) bufferHeight;

        setupImGui();

        cocoaWindow = glfwGetCocoaWindow(window);
        [cocoaWindow setAcceptsMouseMovedEvents:YES];
        [cocoaWindow setCollectionBehavior:NSWindowCollectionBehaviorFullScreenPrimary];

        layer = [CAMetalLayer layer];
        layer.device = device;
        layer.pixelFormat = MTLPixelFormatBGRA8Unorm;
        cocoaWindow.contentView.layer = layer;
        cocoaWindow.contentView.wantsLayer = YES;

        layer.drawableSize = CGSizeMake(bufferWidth, bufferHeight);

        lastFrameTime = glfwGetTime();
    }

    ~Window() {
        ImGui_ImplMetal_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    void setupImGui() const {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        (void) io;

        ImGui_ImplGlfw_InitForOther(window, true);
        ImGui_ImplMetal_Init(device);
        ImGui::StyleColorsDark();
    }

    void prepareImGuiFrame(MTLRenderPassDescriptor* renderPassDescriptor) {
        ImGui_ImplMetal_NewFrame(renderPassDescriptor);
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void drawImGuiDemoWindow() {
        bool show_demo_window = true;
        ImGui::ShowDemoWindow(&show_demo_window);
    }

    void drawImGuiSideBar(std::vector<std::shared_ptr<Surface>>& surfaces) {// add sliders now
        static std::vector<uint8_t> showSurface(surfaces.size(), 1);

        ImGui::SetNextWindowPos(ImVec2(5, 5), ImGuiCond_Always);
        ImGui::SetNextWindowSize(ImVec2(sideBarWidth, height - 10), ImGuiCond_FirstUseEver);
        if (ImGui::Begin("3D Functions", nullptr), ImGuiWindowFlags_NoMove) {

            // Input
            static char buf[512] = "x^2 + y^2";
            ImGui::InputText("Input here", buf, IM_ARRAYSIZE(buf));
            ImGui::SameLine();
            drawImGuiHelp("Input your function here. Example: x^2 + y^2");

            if (ImGui::Button("Add 3D Function")) {
                surfaces.push_back(std::make_shared<Surface>(device, buf, grid));
                showSurface.push_back(1);
            }

            // sliders
            static float a = 0;
            ImGui::TextUnformatted("Sliders");
            ImGui::DragFloat("a", &a, 0.01f, -10.0f, 10.0f);

            // Draw surfaces
            for (size_t i = 0; i < surfaces.size(); i++) {
                std::shared_ptr<Surface> surface = surfaces[i];

                Surface::Plot& plot = surface->plots[surface->plot];
                std::string name = std::to_string(i + 1) + " Function z = " + plot.function->getStrExpr() + "##Func" + std::to_string(i);

                bool* show = reinterpret_cast<bool*>(showSurface.data() + i);
                if (ImGui::CollapsingHeader(name.c_str(), show, ImGuiTreeNodeFlags_DefaultOpen)) {
                    if (showSurface[i] == 1) {
                        drawImGuiFunctionPlot(plot, "Plot Function ##F" + std::to_string(i));
                        drawImGuiFunctionPlot(surface->plots[surface->dx], "Plot Derivative w.r.t x ##DDX" + std::to_string(i));
                        drawImGuiFunctionPlot(surface->plots[surface->dy], "Plot Derivative w.r.t y ##DDY" + std::to_string(i));
                    } else {
                        removeSurface(surfaces, showSurface, i);
                    }
                } else {
                    if (showSurface[i] == 0) {
                        removeSurface(surfaces, showSurface, i);
                    }
                }
            }

            ImGui::End();
        }
    }
    void removeSurface(std::vector<std::shared_ptr<Surface>>& surfaces, std::vector<uint8_t>& showSurface, size_t i) const {
        surfaces.erase(surfaces.begin() + i);
        showSurface.erase(showSurface.begin() + i);
    }

    void drawImGuiFunctionPlot(Surface::Plot& plot, const std::string& str) const {
        if (plot.function == nullptr || plot.function->getExpr() == nullptr) {
            return;
        }

        ImGui::Checkbox(str.c_str(), &plot.render);
        std::string colorName = "Color##" + str;
        ImGui::ColorEdit4(colorName.c_str(), plot.color, ImGuiColorEditFlags_Float);
        drawImGuiTexture(plot.texture->metalTexture);
    }

    void drawImGuiHelp(const char* message) {
        ImGui::TextDisabled("(?)");
        if (ImGui::IsItemHovered()) {
            ImGui::BeginTooltip();
            ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
            ImGui::TextUnformatted(message);
            ImGui::PopTextWrapPos();
            ImGui::EndTooltip();
        }
    }

    void drawImGuiTexture(id<MTLTexture> texture) const {
        ImGui::Image((__bridge ImTextureID) texture, ImVec2(texture.width, texture.height), ImVec2(0, 1), ImVec2(1, 0));
    }

    void drawImGuiFrame(id<MTLCommandBuffer> commandBuffer, id<MTLRenderCommandEncoder> encoder) {
        ImGui::Render();
        ImGui_ImplMetal_RenderDrawData(ImGui::GetDrawData(), commandBuffer, encoder);
    }

    void drawImGuiTimeWindow() const {
        const ImVec2& size = ImVec2(130, 80);

        ImGui::SetNextWindowPos(ImVec2(width - size.x - 10, 10), ImGuiCond_Always);
        ImGui::SetNextWindowSize(size, ImGuiCond_Always);
        if (ImGui::Begin("FPS", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings)) {
            ImGui::Text("dt: %f ms", deltaTime * 1000.0f);
            ImGui::Text("t : %f s", glfwGetTime() - renderStartTime);
            ImGui::Text("%f FPS", 1 / deltaTime);
            ImGui::Text("%d frames", frames);
            ImGui::End();
        }
    }

    ImVec2 getMouseDragDelta() const {
        ImGuiIO& io = ImGui::GetIO();
        if (io.MousePos.x < sideBarWidth + 100 || !io.MouseDown[ImGuiMouseButton_Left]) {
            return {0, 0};
        }

        return io.MouseDelta;
    }

    ImVec2 getMouseScrollDelta() const {
        ImGuiIO& io = ImGui::GetIO();

        if (io.MousePos.x < sideBarWidth + 15) {
            return {0.0f, 0.0f};
        }

        return {io.MouseWheelH, io.MouseWheel};
    }

    bool shouldClose() const {
        return glfwWindowShouldClose(window);
    }

    bool update() {
        if (renderStartTime == 0.0) {
            renderStartTime = glfwGetTime();
        }

        frames++;
        double currentTime = glfwGetTime();
        deltaTime = currentTime - lastFrameTime;
        lastFrameTime = currentTime;
        glfwPollEvents();

        int prevWidth = bufferWidth;
        int prevHeight = bufferHeight;

        glfwGetFramebufferSize(window, &bufferWidth, &bufferHeight);

        if (prevWidth != bufferWidth || prevHeight != bufferHeight) {
            glfwGetWindowSize(window, &width, &height);
            glfwGetWindowContentScale(window, &scaleX, &scaleY);
            bufferAspect = (float) bufferWidth / (float) bufferHeight;
            return true;
        }
        return false;
    }

public:
    id<MTLDevice> device;
    const Grid& grid;
    const char* title;
    GLFWwindow* window{};
    NSWindow* cocoaWindow;
    CAMetalLayer* layer;
    double deltaTime{};
    double lastFrameTime{};
    int frames{};
    double renderStartTime{};
    int width = 0, height = 0;
    int bufferWidth = 0, bufferHeight = 0;
    float bufferAspect = 0.0;
    float scaleX = 0.0, scaleY = 0.0;
    int sideBarWidth = 450;
};

#endif//COMPUTERALGEBRASYSTEM_WINDOW_H
