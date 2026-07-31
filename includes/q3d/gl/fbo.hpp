#pragma once

#include <glm/vec2.hpp>
#include <q3d/res/ptr.hpp>
#include <q3d/gl/vao.hpp>
#include <q3d/gl/vbo.hpp>
#include <q3d/gl/ibo.hpp>
#include <q3d/gl/shader.hpp>
#include <q3d/gl/texture.hpp>
#include <q3d/window/screen.hpp>

namespace q3d::gl {

class Fbo {
private:
    unsigned int id;
    unsigned int rbo;
    glm::vec2 size;

    ptr<gl::Texture> texture;
public:
    Fbo(glm::vec2 size);
    void updateSize(glm::vec2 newSize);
    void bind() const;
    static void unbind();
    ptr<gl::Texture> getTexture() const { return texture; }
};

} // namespace q3d::gl
