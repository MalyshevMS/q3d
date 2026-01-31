#include <q3d/gl/vbo.hpp>
#include <glad/glad.h>

using namespace q3d;

unsigned int gl::buffer::getCount(DataType type) {
    switch(type) {
        case DataType::float1:
        case DataType::int1:
            return 1;
        case DataType::float2:
        case DataType::int2:
            return 2;
        case DataType::float3:
        case DataType::int3:
            return 3;
        case DataType::float4:
        case DataType::int4:
            return 4;
    }

    return 0;
}

unsigned int gl::buffer::getSize(DataType type) {
    switch(type) {
        case DataType::int1:
        case DataType::int2:
        case DataType::int3:
        case DataType::int4:
            return sizeof(GLint) * getCount(type);

        case DataType::float1:
        case DataType::float2:
        case DataType::float3:
        case DataType::float4:
            return sizeof(GLfloat) * getCount(type);
    }

    return 0;
}

unsigned int gl::buffer::getGlType(DataType type) {
    switch(type) {
        case DataType::int1:
        case DataType::int2:
        case DataType::int3:
        case DataType::int4:
            return GL_INT;

        case DataType::float1:
        case DataType::float2:
        case DataType::float3:
        case DataType::float4:
            return GL_FLOAT;
    }

    return 0;
}

gl::buffer::Layout::Layout(std::initializer_list<Element> lst)
 : elements(std::move(lst)) {
    unsigned int offset = 0;
    stride = 0;

    for (auto& el : elements) {
        el.offset = offset;
        offset += el.size;
        stride += el.size;
    }
}

const std::vector<gl::buffer::Element> &gl::buffer::Layout::getElements() const {
    return elements;
}

unsigned int gl::Vbo::toGlMode(Mode mode) {
    switch (mode) {
        case Mode::Static:
            return GL_STATIC_DRAW;
        case Mode::Dynamic:
            return GL_DYNAMIC_DRAW;
        case Mode::Stream:
            return GL_STREAM_DRAW;
        default:
            return GL_STATIC_DRAW;
    }
}

gl::Vbo::Vbo(const void *data, const unsigned int size, buffer::Layout layout, Mode mode)
 : layout(layout) {
    glGenBuffers(1, &id);
    bind();
    glBufferData(GL_ARRAY_BUFFER, size, data, toGlMode(mode));
    
    auto stride = layout.getStride();
    if (stride > 0) {
        vertexCount = size / stride;
    }
}

gl::Vbo::~Vbo() {
    glDeleteBuffers(1, &id);
}

void gl::Vbo::bind() {
    glBindBuffer(GL_ARRAY_BUFFER, id);
}

void gl::Vbo::unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0u);
}
