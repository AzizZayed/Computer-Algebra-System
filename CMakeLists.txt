cmake_minimum_required(VERSION 3.2)
project(ComputerAlgebraSystem)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

if (CMAKE_BUILD_TYPE MATCHES Debug)
    add_compile_options(
            -Wall
            -Wextra
            -fsanitize=address
            -fsanitize=undefined
            -fno-sanitize-recover=all
            -fno-omit-frame-pointer
    )
    add_link_options(
            -fsanitize=address
            -fsanitize=undefined
            -fno-sanitize-recover=all
            -fno-omit-frame-pointer
    )
endif()

add_subdirectory("cas")
add_subdirectory(extern/glfw)
include_directories(
        extern/glfw/include
        extern/imgui/
        extern/imgui/backends)

if (APPLE)
    message(STATUS "Apple OS detected - Using METAL for graphics")
    set(MAIN_FILE "src/render/metal/main.mm")
    set(HEADERS_AMD_SOURCES
            src/render/metal/metal_math.h
            src/render/metal/metal_types.h
            src/render/metal/shader.metal
            extern/imgui/imgui.cpp
            extern/imgui/imgui_demo.cpp
            extern/imgui/imgui_draw.cpp
            extern/imgui/imgui_tables.cpp
            extern/imgui/imgui_widgets.cpp
            extern/imgui/backends/imgui_impl_glfw.cpp
            extern/imgui/backends/imgui_impl_metal.mm)

    set(LINK_LIBS glfw
            "-framework Metal"
            "-framework QuartzCore"
            "-framework Cocoa"
            "-framework MetalKit"
            "-framework ModelIO")
elseif (WIN32 OR LINUX)
    message(STATUS "Windows or Linux OS detected - Using OpenGL for graphics")
    set(MAIN_FILE "src/render/opengl/main.cpp")
    # TODO add files and libs
endif()

add_executable(${PROJECT_NAME} ${MAIN_FILE} ${HEADERS_AMD_SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE "cas" ${LINK_LIBS})