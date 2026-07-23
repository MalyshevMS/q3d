#include <q3d/gl/ssbo.hpp>
#include <glad/glad.h>

using namespace q3d;
using namespace gl;

Ssbo::Ssbo(unsigned int binding)
 : binding(binding) {
    glGenBuffers(1, &id);
}

Ssbo::Ssbo(Ssbo&& other) noexcept
 : id(other.id), binding(other.binding) {
    other.id = 0;
}

Ssbo::~Ssbo() {
    if (id) glDeleteBuffers(1, &id);
}

void Ssbo::bind() const {
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, id);
}

void Ssbo::bindBase() const {
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, binding, id);
}

void Ssbo::unbind() {
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

void Ssbo::updateData(const void* data, unsigned int size) {
    bind();
    glBufferData(GL_SHADER_STORAGE_BUFFER, size, data, GL_DYNAMIC_DRAW);
    bindBase();
}
