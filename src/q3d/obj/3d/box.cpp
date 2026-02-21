#include <q3d/obj/3d/box.hpp>

using namespace q3d::object;

Box::Box(ptr<gl::Shader> shader, phys::Transform transform, ptr<gl::Texture> texture)
 : core::Object(shader, transform, texture) {
    const float verticies[] = {
    //    X     Y     Z             U               V
        // Front (+Z)
        -1.f, -1.f,  1.f,          0.0f,           0.0f,
         1.f, -1.f,  1.f,          texture->uv.x,  0.0f,
         1.f,  1.f,  1.f,          texture->uv.x,  texture->uv.x,
        -1.f,  1.f,  1.f,          0.0f,           texture->uv.x,

        // Back (-Z)
         1.f, -1.f, -1.f,          0.0f,           0.0f,
        -1.f, -1.f, -1.f,          texture->uv.x,  0.0f,
        -1.f,  1.f, -1.f,          texture->uv.x,  texture->uv.x,
         1.f,  1.f, -1.f,          0.0f,           texture->uv.x,

        // Left (-X)
        -1.f, -1.f, -1.f,          0.0f,           0.0f,
        -1.f, -1.f,  1.f,          texture->uv.x,  0.0f,
        -1.f,  1.f,  1.f,          texture->uv.x,  texture->uv.x,
        -1.f,  1.f, -1.f,          0.0f,           texture->uv.x,

        // Right (+X)
         1.f, -1.f,  1.f,          0.0f,           0.0f,
         1.f, -1.f, -1.f,          texture->uv.x,  0.0f,
         1.f,  1.f, -1.f,          texture->uv.x,  texture->uv.x,
         1.f,  1.f,  1.f,          0.0f,           texture->uv.x,

        // Top (+Y)
        -1.f,  1.f,  1.f,          0.0f,           0.0f,
         1.f,  1.f,  1.f,          texture->uv.x,  0.0f,
         1.f,  1.f, -1.f,          texture->uv.x,  texture->uv.x,
        -1.f,  1.f, -1.f,          0.0f,           texture->uv.x,

        // Bottom (-Y)
        -1.f, -1.f, -1.f,          0.0f,           0.0f,
         1.f, -1.f, -1.f,          texture->uv.x,  0.0f,
         1.f, -1.f,  1.f,          texture->uv.x,  texture->uv.x,
        -1.f, -1.f,  1.f,          0.0f,           texture->uv.x,
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

    vbo = std::make_unique<gl::Vbo>(verticies, sizeof(verticies), gl::buffer::Layout::l_xyz_uv);
    ibo = std::make_unique<gl::Ibo>(ind, 36);
    vao = std::make_unique<gl::Vao>();

    vao->addVbo(*vbo);
    vao->setIbo(*ibo);
}