cmake_minimum_required(VERSION 3.25 FATAL_ERROR)

set(PROJECT_NAME q3d)

project(${PROJECT_NAME})

set(Q3D_HEADERS
    includes/q3d/window/window.hpp
    includes/q3d/log/log.hpp

    includes/q3d/res/resources.hpp

    includes/q3d/core/color.hpp
    includes/q3d/core/camera.hpp
    includes/q3d/core/active_camera.hpp
    includes/q3d/core/object.hpp

    includes/q3d/gl/gl.hpp
    includes/q3d/gl/shader.hpp
    includes/q3d/gl/vbo.hpp
    includes/q3d/gl/ibo.hpp
    includes/q3d/gl/vao.hpp
    includes/q3d/gl/texture.hpp

    includes/q3d/phys/aabb.hpp
    includes/q3d/phys/transform.hpp

    includes/q3d/obj/2d/plane.hpp
    includes/q3d/obj/3d/box.hpp
)

set(Q3D_SOURCES
    src/q3d/window/window.cpp

    src/q3d/res/resources.cpp

    src/q3d/core/color.cpp
    src/q3d/core/camera.cpp
    src/q3d/core/active_camera.cpp
    src/q3d/core/object.cpp

    src/q3d/gl/gl.cpp
    src/q3d/gl/shader.cpp
    src/q3d/gl/uniform.cpp
    src/q3d/gl/vbo.cpp
    src/q3d/gl/ibo.cpp
    src/q3d/gl/vao.cpp
    src/q3d/gl/texture.cpp
    src/q3d/gl/layouts.cpp

    src//q3d/phys/aabb.cpp
    src//q3d/phys/transform.cpp

    src/q3d/obj/2d/plane.cpp
    src/q3d/obj/3d/box.cpp
)

option(Q3D_STATIC "ON = use static linking, OFF = build as a shared library" OFF)

if (${Q3D_STATIC})
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

# Linking

target_link_libraries(${PROJECT_NAME}
    PUBLIC glfw
    PUBLIC glad
    PUBLIC glm
)