#include <q3d/gl/gl.hpp>
#include <q3d/system/color.hpp>
#include <glad/glad.h>

using namespace q3d;

void gl::clear() {
    glClear(GL_COLOR_BUFFER_BIT);
}

void gl::clearColor(Color color) {
    glClearColor(color.r, color.g, color.b, color.a);
}