#include <q3d/gl/shader.hpp>
#include <q3d/gl/gl.hpp>
#include <q3d/gl/features.hpp>
#include <q3d/window/screen.hpp>
#include <glad/glad.h>

using namespace q3d;
using namespace gl;

Screen::Screen(ptr<gl::Shader> shader, ptr<gl::Texture> texture)
 : shader(shader), texture(texture) {
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

    vbo = std::make_unique<gl::Vbo>(vert, sizeof(vert), gl::buffer::Layout::l_xy_uv);
    ibo = std::make_unique<gl::Ibo>(ind, 6);
    vao = std::make_unique<gl::Vao>();

    vao->addVbo(*vbo);
    vao->setIbo(*ibo);
}

void Screen::draw() const {
    disable(feature::depthTest);
    glClear(GL_COLOR_BUFFER_BIT);
    shader->use();
    texture->use(*shader);
    vao->draw();
}

void Screen::setShader(ptr<Shader> shader) {
    this->shader = shader;
}

void Screen::setTexture(ptr<Texture> texture) {
    this->texture = texture;
}
