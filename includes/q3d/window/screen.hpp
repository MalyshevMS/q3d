#pragma once

#include <q3d/res/ptr.hpp>
#include <q3d/gl/texture.hpp>
#include <q3d/gl/vao.hpp>

namespace q3d {

class Screen {
private:
    ptr<gl::Texture> texture;
    ptr<gl::Shader> shader;

    uptr<gl::Vbo> vbo;
    uptr<gl::Ibo> ibo;
    uptr<gl::Vao> vao;
public:
    Screen(ptr<gl::Shader> shader = nullptr, ptr<gl::Texture> texture = nullptr);

    void setShader(ptr<gl::Shader> shader);
    void setTexture(ptr<gl::Texture> texture);
    void draw() const;
};

}
