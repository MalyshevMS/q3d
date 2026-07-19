#pragma once

#include <glm/vec2.hpp>
#include <q3d/res/ptr.hpp>
#include <q3d/gl/vao.hpp>
#include <q3d/gl/vbo.hpp>
#include <q3d/gl/ibo.hpp>
#include <q3d/gl/shader.hpp>

namespace q3d::gl {

class Fbo {
private:
    unsigned int id;
    unsigned int rbo;
    glm::vec2 size;

    uptr<gl::Vbo> vbo;
    uptr<gl::Ibo> ibo;
    uptr<gl::Vao> vao;
    ptr<gl::Shader> post_shader;
public:
    Fbo(glm::vec2 size, ptr<gl::Shader> postEffectShader);
    void bind() const;
    static void unbind();
    void draw() const;
};

}
