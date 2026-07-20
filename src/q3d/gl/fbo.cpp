#include <q3d/gl/fbo.hpp>
#include <q3d/gl/texture.hpp>
#include <q3d/gl/features.hpp>
#include <q3d/gl/gl.hpp>
#include <q3d/log/log.hpp>
#include <glad/glad.h>
#include <memory>

using namespace q3d;
using namespace gl;

Fbo::Fbo(glm::vec2 size, ptr<gl::Shader> postEffectShader)
: size(size), post_shader(postEffectShader) {
    glGenFramebuffers(1, &id);

    texture = std::make_shared<Texture>(nullptr, size.x, size.y, 3);
    texture->setFilter(Texture::Filter::Linear, Texture::Filter::Linear);
    texture->bindFbo(*this);

    bind();

    glGenRenderbuffers(1, &rbo); // Yeah, I'm not gonna make a dedicated class for this rn
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, size.x, size.y);

    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        log::error("Fbo::Fbo(): Framebuffer isn't complete!");
    }

    const float vert[] = {
        -1.0f,  1.0f,  0.0f, 1.0f,
        -1.0f, -1.0f,  0.0f, 0.0f,
        1.0f, -1.0f,  1.0f, 0.0f,
        1.0f,  1.0f,  1.0f, 1.0f
    };

    const unsigned int ind[] = {
        0, 1, 2,
        2, 3, 0
    };

    vbo = std::make_unique<gl::Vbo>(vert, sizeof(vert), gl::buffer::Layout::l_xyzw);
    ibo = std::make_unique<gl::Ibo>(ind, 6);
    vao = std::make_unique<gl::Vao>();

    vao->addVbo(*vbo);
    vao->setIbo(*ibo);

    unbind();
}

void Fbo::updateSize(glm::vec2 newSize) {
    size = newSize;

    texture->update(nullptr, size.x, size.y, 3);

    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, size.x, size.y);

    bind();
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        log::error("Fbo::updateSize(): Framebuffer isn't complete!");
    }
    unbind();
}

void Fbo::bind() const {
    glBindFramebuffer(GL_FRAMEBUFFER, id);
}

void Fbo::unbind() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Fbo::draw() const {
    disable(feature::depthTest);
    glClear(GL_COLOR_BUFFER_BIT);
    post_shader->use();
    texture->use(*post_shader);
    vao->draw();
}
