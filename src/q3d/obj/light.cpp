#include <q3d/obj/light.hpp>

using namespace q3d;
using namespace gl;
using namespace core;
using namespace object;

LightObj::LightObj(ptr<Shader> shader, phys::Transform transform)
 : core::Object(shader, nullptr, transform) {
    const float vertices[] = {
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f, -0.5f, -0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,
    };

    const unsigned int ind[] = {
        // (+X)
        0, 1, 3,
        0, 3, 2,

        // (-X)
        4, 6, 7,
        4, 7, 5,

        // (+Y)
        4, 0, 1,
        4, 1, 5,

        // (-Y)
        6, 7, 3,
        6, 3, 2,

        // (+Z)
        4, 6, 2,
        4, 2, 0,

        // (-Z)
        1, 3, 7,
        1, 7, 5
    };

    vbo = std::make_unique<Vbo>(vertices, sizeof(vertices), buffer::Layout::l_xyz);
    ibo = std::make_unique<Ibo>(ind, 6);
    vao = std::make_unique<Vao>();

    vao->addVbo(*vbo);
    vao->setIbo(*ibo);
}
