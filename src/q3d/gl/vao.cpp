#include <q3d/gl/vao.hpp>
#include <glad/glad.h>

q3d::gl::Vao::Vao() {
    glGenVertexArrays(1, &id);
}

q3d::gl::Vao::~Vao() {
    glDeleteVertexArrays(1, &id);
}

void q3d::gl::Vao::bind() {
    glBindVertexArray(id);
}

void q3d::gl::Vao::unbind() {
    glBindVertexArray(0);
}

void q3d::gl::Vao::addVbo(Vbo &vbo) {
    bind();
    vbo.bind();

    for (auto& el : vbo.getLayout().getElements()) {
        glVertexAttribPointer(
            elCount,
            el.count,
            el.glType,
            GL_FALSE,
            vbo.getLayout().getStride(),
            reinterpret_cast<void*>(el.offset) // Dear Khronos group, what a fuck is that syntax?
        );
        glEnableVertexAttribArray(elCount++);
    }
    
    vertexCount = vbo.getVertexCount();
}

void q3d::gl::Vao::setIbo(Ibo &ibo) {
    bind();
    ibo.bind();
    indCount = ibo.getCount();
}

void q3d::gl::Vao::draw(unsigned int method) {
    bind();

    if(indCount > 0) {
        glDrawElements(method, indCount, GL_UNSIGNED_INT, nullptr);
    } else {
        glDrawArrays(method, 0, vertexCount);
    }
}
