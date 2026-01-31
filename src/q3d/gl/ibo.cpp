#include <q3d/gl/ibo.hpp>
#include <glad/glad.h>

using namespace q3d;

gl::Ibo::Ibo(const void *data, const unsigned int count, const Vbo::Mode mode)
 : count(count) {
    glGenBuffers(1, &id);
    bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, Vbo::toGlMode(mode));
}

gl::Ibo::~Ibo() {
    glDeleteBuffers(1, &id);
}

void gl::Ibo::bind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

void gl::Ibo::unbind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
