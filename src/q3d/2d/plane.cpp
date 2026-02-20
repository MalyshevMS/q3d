#include <q3d/2d/plane.hpp>

using namespace q3d::q2d;

Plane::Plane(ptr<gl::Shader> shader, phys::Transform transform, ptr<gl::Texture> texture)
 : core::Object(shader, transform, texture) {
    const float verticies[] = {
    //   X      Y      Z             U              V
       -1.f,  -1.f,   0.f,          0.f,           0.f,
        1.f,  -1.f,   0.f,          texture->uv.x, 0.f,
        1.f,   1.f,   0.f,          texture->uv.x, texture->uv.y,
       -1.f,   1.f,   0.f,          0.f,           texture->uv.y,
    };

    const unsigned int ind[] = {
        0, 1, 2,
        2, 3, 0,
    };

    const gl::buffer::Layout l_xyz_uv = {
        gl::buffer::DataType::float3,
        gl::buffer::DataType::float2,
    };

    vbo = std::make_unique<gl::Vbo>(verticies, sizeof(verticies), l_xyz_uv);
    ibo = std::make_unique<gl::Ibo>(ind, 6);
    vao = std::make_unique<gl::Vao>();

    vao->addVbo(*vbo);
    vao->setIbo(*ibo);
}