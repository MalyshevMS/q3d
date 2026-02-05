#include <q3d/gl/texture.hpp>
#include <q3d/gl/shader.hpp>
#include <glad/glad.h>

using namespace q3d;

gl::Texture::Texture(const Image data, unsigned int width, unsigned int height, unsigned int channels) {
    glGenTextures(1, &id);

    wrapMode(WrapMode::Repeat, WrapMode::Repeat);
    setFilter(Filter::LinearMMLinear, Filter::Linear);
    
    GLenum fmt = GL_RGB;
    if (channels == 4) fmt = GL_RGBA;

    bind();

    glTexImage2D(GL_TEXTURE_2D, 0, fmt, width, height, 0, fmt, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    unbind();
}

void gl::Texture::bind() {
    glBindTexture(GL_TEXTURE_2D, id);
}

void gl::Texture::unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}

void gl::Texture::use(Shader& shader, const unsigned int unit) {
    glActiveTexture(GL_TEXTURE0 + unit);
    bind();
    shader.uniform("u_texture", 0);
}

static GLenum wrapToGL(gl::Texture::WrapMode wrap) {
    using enum gl::Texture::WrapMode;
    
    switch (wrap) {
        case ClampToEdge:       return GL_CLAMP_TO_EDGE;
        case ClampToBorder:     return GL_CLAMP_TO_BORDER;
        case MirroredRepeat:    return GL_MIRRORED_REPEAT;
        case Repeat:            return GL_REPEAT;
        case MirrorClampToEdge: return GL_MIRROR_CLAMP_TO_EDGE;
    }

    return 0;
}

void gl::Texture::wrapMode(WrapMode wrapS, WrapMode wrapT) {
    bind();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapToGL(wrapS));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapToGL(wrapT));

    unbind();
}

static GLenum filterToGL(gl::Texture::Filter filter) {
    using enum gl::Texture::Filter;

    switch (filter) {
        case Nearest:           return GL_NEAREST;
        case Linear:            return GL_LINEAR;
        case LinearMMLinear:    return GL_LINEAR_MIPMAP_LINEAR;
        case LinearMMNearest:   return GL_LINEAR_MIPMAP_NEAREST;
        case NearestMMLinear:   return GL_NEAREST_MIPMAP_LINEAR;
        case NearestMMNearest:  return GL_NEAREST_MIPMAP_NEAREST;
    }

    return 0;
}

void gl::Texture::setFilter(Filter min, Filter mag) {
    bind();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterToGL(min));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterToGL(mag));

    unbind();
}