#include <q3d/gl/gl.hpp>
#include <q3d/system/color.hpp>
#include <glad/glad.h>

void q3d::gl::clear() {
    glClear(GL_COLOR_BUFFER_BIT);
}

void q3d::gl::clearColor(q3d::Color color) {
    glClearColor(color.r, color.g, color.b, color.a);
}