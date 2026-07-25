#include <q3d/gl/shadow_map.hpp>
#include <glad/glad.h>

using namespace q3d;
using namespace gl;

ShadowMap::ShadowMap(unsigned int res, unsigned int maxLights)
 : width(res), height(res), maxLayers(maxLights) {
    glGenFramebuffers(1, &fbo);

    glGenTextures(1, &depthMap);
    glBindTexture(GL_TEXTURE_2D_ARRAY, depthMap);
    glTexImage3D(
        GL_TEXTURE_2D_ARRAY, 0, GL_DEPTH_COMPONENT,
        width, height, maxLayers, 0,
        GL_DEPTH_COMPONENT, GL_FLOAT, nullptr
    );

    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

    float borderColor[] = { 1.f, 1.f, 1.f, 1.f };
    glTexParameterfv(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BORDER_COLOR, borderColor);

    // glFramebufferTexture3D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D_ARRAY, depthMap, 0);

    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

ShadowMap::~ShadowMap() {
    if (fbo) glDeleteFramebuffers(1, &fbo);
    if (depthMap) glDeleteTextures(1, &depthMap);
}

void ShadowMap::bindWrite(unsigned int layer) const {
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    glFramebufferTextureLayer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthMap, 0, layer);

    glViewport(0, 0, width, height);
    glClear(GL_DEPTH_BUFFER_BIT);
}

void ShadowMap::bindRead(unsigned int unit) const {
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D_ARRAY, depthMap);
}
