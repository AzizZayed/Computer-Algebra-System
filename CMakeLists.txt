cmake_minimum_required(VERSION 3.12)
project(ComputerAlgebraSystem
        VERSION 0.0.1
        DESCRIPTION "A computer algebra system"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

include(FetchContent)

if (CMAKE_BUILD_TYPE MATCHES Debug)
    add_compile_options(
            -Wall
            -Wextra
            -fsanitize=address
            -fsanitize=undefined
    )
    add_link_options(
            -fsanitize=address
            -fsanitize=undefined
    )
endif()

add_subdirectory("cas")

FetchContent_Declare(glfw
        GIT_REPOSITORY https://github.com/glfw/glfw
        GIT_TAG 3.3.8)
FetchContent_MakeAvailable(glfw)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

FetchContent_Declare(imgui
        GIT_REPOSITORY https://github.com/ocornut/imgui
        GIT_TAG v1.89.1)
FetchContent_MakeAvailable(imgui)
include_directories(${imgui_SOURCE_DIR}/ ${imgui_SOURCE_DIR}/backends)

if (CMAKE_SYSTEM_NAME MATCHES "Darwin")
    message(STATUS "Apple OS detected - Using METAL for graphics")
    set(MAIN_FILE "src/render/metal/main.mm")
    set(HEADERS_AMD_SOURCES
            src/render/metal/metal_math.h
            src/render/metal/metal_types.h
            src/render/metal/Window.h
            src/render/metal/Grid.h
            src/render/metal/Surface.h
            src/render/metal/shader.metal
            ${imgui_SOURCE_DIR}/imgui.cpp
            ${imgui_SOURCE_DIR}/imgui_demo.cpp
            ${imgui_SOURCE_DIR}/imgui_draw.cpp
            ${imgui_SOURCE_DIR}/imgui_tables.cpp
            ${imgui_SOURCE_DIR}/imgui_widgets.cpp
            ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
            ${imgui_SOURCE_DIR}/backends/imgui_impl_metal.mm)

    set(LINK_LIBS glfw
            "-framework Metal"
            "-framework QuartzCore"
            "-framework Cocoa"
            "-framework MetalKit"
            "-framework ModelIO")
elseif (CMAKE_SYSTEM_NAME MATCHES "Linux" OR CMAKE_SYSTEM_NAME MATCHES "Windows")
    message(STATUS "Windows or Linux OS detected - Using OpenGL for graphics")
    set(MAIN_FILE "src/render/opengl/main.cpp")
    set(HEADERS_AMD_SOURCES "")
    set(LINK_LIBS glfw)

    # TODO add files and libs
endif()

add_executable(${PROJECT_NAME} ${MAIN_FILE} ${HEADERS_AMD_SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE "cas" ${LINK_LIBS})