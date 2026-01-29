#include <q3d/gl/gl.hpp>
#include <glad/glad.h>

void q3d::gl::clear() {
    glClear(GL_COLOR_BUFFER_BIT);
}