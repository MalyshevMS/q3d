#include <utility>
#include <q3d/gl/cubemap.hpp>
#include <glad/glad.h>

using namespace q3d;
using namespace gl;

CubeMap::CubeMap(unsigned int resolution, unsigned int count)
 : width(resolution), height(resolution), count(count) {
    glGenFramebuffers(1, &fbo);

    glGenTextures(1, &cubemap);
    glBindTexture(GL_TEXTURE_CUBE_MAP_ARRAY, cubemap);
    GLsizei layerCount = static_cast<GLsizei>(count * 6);

    glTexImage3D(
        GL_TEXTURE_CUBE_MAP_ARRAY, 0, GL_DEPTH_COMPONENT32F,
        width, height, layerCount, 0,
        GL_DEPTH_COMPONENT, GL_FLOAT, nullptr
    );

    glTexParameteri(GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

CubeMap::~CubeMap() {
    if (cubemap) glDeleteTextures(1, &cubemap);
    if (fbo) glDeleteFramebuffers(1, &fbo);
}

CubeMap::CubeMap(CubeMap&& other) noexcept
 : fbo(std::exchange(other.fbo, 0)),
   cubemap(std::exchange(other.cubemap, 0)),
   width(other.width),
   height(other.height),
   count(other.count) {}

CubeMap& CubeMap::operator=(CubeMap&& other) noexcept {
    if (this != &other) {
        if (fbo) glDeleteFramebuffers(1, &fbo);
        if (cubemap) glDeleteTextures(1, &cubemap);

        fbo = std::exchange(other.fbo, 0);
        cubemap = std::exchange(other.cubemap, 0);
        width = other.width;
        height = other.height;
        count = other.count;
    }
    return *this;
}

void CubeMap::bindWrite(unsigned int layer) const {
    glViewport(0, 0, width, height);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, cubemap, 0);
    glClear(GL_DEPTH_BUFFER_BIT);
}

void CubeMap::bindRead(unsigned int unit) const {
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_CUBE_MAP_ARRAY, cubemap);
}
