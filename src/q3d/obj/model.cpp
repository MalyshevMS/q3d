#include <q3d/obj/model.hpp>
#include <q3d/log/log.hpp>

using namespace q3d;
using namespace object;

Model::Model(ptr<gl::Shader> shader, const ObjData& objData, ptr<gl::Texture> texture, phys::Transform transform)
 : core::Object(shader, texture, transform) {

    if (objData.vertices.empty() || objData.indices.empty()) {
        q3d::log::error("Model::Model(): Cannot create buffers - no data");
        return;
    }

    vbo = std::make_unique<gl::Vbo>(
        objData.vertices.data(),
        objData.vertices.size() * sizeof(Vertex),
        gl::buffer::Layout::l_xyz_uv_nnn
    );

    ibo = std::make_unique<gl::Ibo>(objData.indices.data(), objData.indices.size());
    vao = std::make_unique<gl::Vao>();

    vao->addVbo(*vbo);
    vao->setIbo(*ibo);

    features[gl::feature::cullFace] = true;
}
