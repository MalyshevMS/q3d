cmake_minimum_required(VERSION 3.25 FATAL_ERROR)

set(PROJECT_NAME q3d)

project(${PROJECT_NAME})

set(Q3D_HEADERS
    includes/q3d/window/window.hpp
    includes/q3d/window/screen.hpp
    includes/q3d/log/log.hpp

    includes/q3d/res/resources.hpp

    includes/q3d/core/color.hpp
    includes/q3d/core/camera.hpp
    includes/q3d/core/active_camera.hpp
    includes/q3d/core/object.hpp
    includes/q3d/core/scene.hpp

    includes/q3d/gl/gl.hpp
    includes/q3d/gl/shader.hpp
    includes/q3d/gl/vbo.hpp
    includes/q3d/gl/ibo.hpp
    includes/q3d/gl/vao.hpp
    includes/q3d/gl/fbo.hpp
    includes/q3d/gl/ssbo.hpp
    includes/q3d/gl/texture.hpp
    includes/q3d/gl/shadow_map.hpp
    includes/q3d/gl/cubemap.hpp

    includes/q3d/phys/aabb.hpp
    includes/q3d/phys/transform.hpp

    includes/q3d/obj/plane.hpp
    includes/q3d/obj/box.hpp
    includes/q3d/obj/model.hpp
    includes/q3d/obj/dirlight.hpp
    includes/q3d/obj/spotlight.hpp
    includes/q3d/obj/pointlight.hpp

    includes/q3d/ui/canvas.hpp
    includes/q3d/ui/font.hpp
    includes/q3d/ui/text.hpp
)

set(Q3D_SOURCES
    src/q3d/window/window.cpp
    src/q3d/window/screen.cpp

    src/q3d/res/resources.cpp
    src/q3d/res/texture_loader.cpp
    src/q3d/res/shader_loader.cpp
    src/q3d/res/model_loader.cpp
    src/q3d/res/font_loader.cpp
    src/q3d/res/material_loader.cpp
    src/q3d/res/fs.cpp

    src/q3d/core/color.cpp
    src/q3d/core/camera.cpp
    src/q3d/core/active_camera.cpp
    src/q3d/core/object.cpp
    src/q3d/core/scene.cpp

    src/q3d/gl/gl.cpp
    src/q3d/gl/shader.cpp
    src/q3d/gl/uniform.cpp
    src/q3d/gl/vbo.cpp
    src/q3d/gl/ibo.cpp
    src/q3d/gl/vao.cpp
    src/q3d/gl/fbo.cpp
    src/q3d/gl/ssbo.cpp
    src/q3d/gl/texture.cpp
    src/q3d/gl/layouts.cpp
    src/q3d/gl/shadow_map.cpp
    src/q3d/gl/cubemap.cpp

    src/q3d/phys/aabb.cpp
    src/q3d/phys/transform.cpp

    src/q3d/obj/plane.cpp
    src/q3d/obj/box.cpp
    src/q3d/obj/model.cpp
    src/q3d/obj/light.cpp
    src/q3d/obj/dirlight.cpp
    src/q3d/obj/spotlight.cpp
    src/q3d/obj/pointlight.cpp

    src/q3d/ui/canvas.cpp
    src/q3d/ui/font.cpp
    src/q3d/ui/text.cpp
)

option(Q3D_STATIC "ON = use static linking, OFF = use dynamic linking" OFF)

if(${Q3D_STATIC})
    add_library(${PROJECT_NAME} STATIC ${Q3D_HEADERS} ${Q3D_SOURCES})
else()
    add_library(${PROJECT_NAME} SHARED ${Q3D_HEADERS} ${Q3D_SOURCES})
endif()

target_include_directories(${PROJECT_NAME} PUBLIC includes)

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 23)

# Dependencies

set(GLAD_STATIC ${Q3D_STATIC})

add_subdirectory(ext/glfw)

add_subdirectory(ext/glad-core/glad)

add_subdirectory(ext/glm)

set(FT_DISABLE_ZLIB TRUE CACHE BOOL "Disable ZLib" FORCE)
set(FT_DISABLE_BZIP2 TRUE CACHE BOOL "Disable Bzip2" FORCE)
set(FT_DISABLE_PNG TRUE CACHE BOOL "Disable PNG" FORCE)
set(FT_DISABLE_HARFBUZZ TRUE CACHE BOOL "Disable Harfbuzz" FORCE)
set(FT_DISABLE_BROTLI TRUE CACHE BOOL "Disable Brotli" FORCE)

set(BUILD_SHARED_LIBS ON CACHE BOOL "Build shared libraries" FORCE)

add_subdirectory(ext/freetype)

add_subdirectory(ext/nlohmann_json)

# Linking

target_link_libraries(${PROJECT_NAME}
    PUBLIC glfw
    PUBLIC glad
    PUBLIC glm
    PUBLIC freetype
    PUBLIC nlohmann_json::nlohmann_json
)
