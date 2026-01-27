cmake_minimum_required(VERSION 3.25 FATAL_ERROR)

set(PROJECT_NAME q3d)

project(${PROJECT_NAME})

set(Q3D_HEADERS
    includes/q3d/window/window.hpp
)

set(Q3D_SOURCES
    src/q3d/window/window.cpp
)

add_library(${PROJECT_NAME} SHARED ${Q3D_HEADERS} ${Q3D_SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC includes)

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 23)