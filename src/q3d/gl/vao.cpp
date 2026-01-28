#include <q3d/gl/vao.hpp>
#include <glad/glad.h>

unsigned int q3d::gl::methodToGl(DrawMethod method) {
    using enum DrawMethod;

    switch (method) {
        case Points:           return GL_POINTS;
        case Lines:            return GL_LINES;
        case LineStrip:        return GL_LINE_STRIP;
        case LineLoop:         return GL_LINE_LOOP;
        case Triangles:        return GL_TRIANGLES;
        case TriangleStrip:    return GL_TRIANGLE_STRIP;
        case TriangleFan:      return GL_TRIANGLE_FAN;
        case Patches:          return GL_PATCHES;
    }

    return GL_TRIANGLES;
}

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

void q3d::gl::Vao::draw(DrawMethod method) {
    bind();

    if(indCount > 0) {
        glDrawElements(methodToGl(method), indCount, GL_UNSIGNED_INT, nullptr);
    } else {
        glDrawArrays(methodToGl(method), 0, vertexCount);
    }
}
