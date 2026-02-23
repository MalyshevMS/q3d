#include <q3d/obj/3d/model.hpp>
#include <q3d/log/log.hpp>
#include <sstream>
#include <algorithm>

using namespace q3d::object;


Model::Model(ptr<gl::Shader> shader, const Resources::ObjData& objData, phys::Transform transform, ptr<gl::Texture> texture)
 : core::Object(shader, transform, texture) {
    
    if (objData.positions.empty() || objData.indices.empty()) {
        q3d::log::error("Model: Cannot create buffers - no data!");
        return;
    }

    std::vector<float> vertexData;
    vertexData.reserve(objData.positions.size() * 5);

    for (size_t i = 0; i < objData.positions.size(); i++) {
        vertexData.push_back(objData.positions[i].x);
        vertexData.push_back(objData.positions[i].y);
        vertexData.push_back(objData.positions[i].z);
        vertexData.push_back(objData.texCoords[i].x);
        vertexData.push_back(objData.texCoords[i].y);
    }

    vbo = std::make_unique<gl::Vbo>(vertexData.data(), vertexData.size() * sizeof(float), gl::buffer::Layout::l_xyz_uv);
    ibo = std::make_unique<gl::Ibo>(objData.indices.data(), objData.indices.size());
    vao = std::make_unique<gl::Vao>();

    vao->addVbo(*vbo);
    vao->setIbo(*ibo);

    features.push_back(gl::feature::cullFace);
}
