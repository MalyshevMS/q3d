#include <q3d/obj/3d/box.hpp>

using namespace q3d;
using namespace object;

Box::Box(ptr<gl::Shader> shader, ptr<gl::Texture> texture, phys::Transform transform)
 : core::Object(shader, texture, transform) {
    const float verticies[] = {
    //    X     Y     Z             U               V                     NX   NY   NZ
        // Front (+Z)
        -1.f, -1.f,  1.f,          0.0f,           0.0f,                  0.f,  0.f,  1.f,
         1.f, -1.f,  1.f,          texture->uv.x,  0.0f,                  0.f,  0.f,  1.f,
         1.f,  1.f,  1.f,          texture->uv.x,  texture->uv.x,         0.f,  0.f,  1.f,
        -1.f,  1.f,  1.f,          0.0f,           texture->uv.x,         0.f,  0.f,  1.f,

        // Back (-Z)
         1.f, -1.f, -1.f,          0.0f,           0.0f,                  0.f,  0.f, -1.f,
        -1.f, -1.f, -1.f,          texture->uv.x,  0.0f,                  0.f,  0.f, -1.f,
        -1.f,  1.f, -1.f,          texture->uv.x,  texture->uv.x,         0.f,  0.f, -1.f,
         1.f,  1.f, -1.f,          0.0f,           texture->uv.x,         0.f,  0.f, -1.f,

        // Left (-X)
        -1.f, -1.f, -1.f,          0.0f,           0.0f,                 -1.f,  0.f,  0.f,
        -1.f, -1.f,  1.f,          texture->uv.x,  0.0f,                 -1.f,  0.f,  0.f,
        -1.f,  1.f,  1.f,          texture->uv.x,  texture->uv.x,        -1.f,  0.f,  0.f,
        -1.f,  1.f, -1.f,          0.0f,           texture->uv.x,        -1.f,  0.f,  0.f,

        // Right (+X)
         1.f, -1.f,  1.f,          0.0f,           0.0f,                  1.f,  0.f,  0.f,
         1.f, -1.f, -1.f,          texture->uv.x,  0.0f,                  1.f,  0.f,  0.f,
         1.f,  1.f, -1.f,          texture->uv.x,  texture->uv.x,         1.f,  0.f,  0.f,
         1.f,  1.f,  1.f,          0.0f,           texture->uv.x,         1.f,  0.f,  0.f,

        // Top (+Y)
        -1.f,  1.f,  1.f,          0.0f,           0.0f,                  0.f,  1.f,  0.f,
         1.f,  1.f,  1.f,          texture->uv.x,  0.0f,                  0.f,  1.f,  0.f,
         1.f,  1.f, -1.f,          texture->uv.x,  texture->uv.x,         0.f,  1.f,  0.f,
        -1.f,  1.f, -1.f,          0.0f,           texture->uv.x,         0.f,  1.f,  0.f,

        // Bottom (-Y)
        -1.f, -1.f, -1.f,          0.0f,           0.0f,                  0.f, -1.f,  0.f,
         1.f, -1.f, -1.f,          texture->uv.x,  0.0f,                  0.f, -1.f,  0.f,
         1.f, -1.f,  1.f,          texture->uv.x,  texture->uv.x,         0.f, -1.f,  0.f,
        -1.f, -1.f,  1.f,          0.0f,           texture->uv.x,         0.f, -1.f,  0.f,
    };

    const unsigned int ind[] = {
        0, 1, 2,
        2, 3, 0,

        4, 5, 6,
        6, 7, 4,

        8, 9, 10,
        10,11, 8,

        12,13,14,
        14,15,12,

        16,17,18,
        18,19,16,

        20,21,22,
        22,23,20
    };

    vbo = std::make_unique<gl::Vbo>(verticies, sizeof(verticies), gl::buffer::Layout::l_xyz_uv_nnn);
    ibo = std::make_unique<gl::Ibo>(ind, 36);
    vao = std::make_unique<gl::Vao>();

    vao->addVbo(*vbo);
    vao->setIbo(*ibo);

    features[gl::feature::cullFace] = true;
}
