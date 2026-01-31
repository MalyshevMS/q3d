#include <q3d/gl/texture.hpp>
#include <q3d/gl/shader.hpp>
#include <glad/glad.h>

using namespace q3d;

gl::Texture::Texture(const Image data, unsigned int width, unsigned int height, unsigned int channels) {
    glGenTextures(1, &id);
    bind();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    GLenum fmt = GL_RGB;
    if (channels == 4) fmt = GL_RGBA;

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