#include <q3d/res/resources.hpp>
#include <q3d/res/vertex.hpp>
#define TINYOBJLOADER_IMPLEMENTATION
#include <q3d/res/tiny_obj_loader.h>
#include <q3d/obj/model.hpp>

using namespace q3d;
using namespace object;

ObjData parseObjFile(const fs::path& path) {
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string warn, err;

    bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, path.c_str());

    if (!warn.empty()) {
        log::warn("parseObjFile('{}'): warning from loader: {}", path.string(), warn);
    }

    if (!err.empty()) {
        log::warn("parseObjFile('{}'): error from loader: {}", path.string(), err);
    }

    if (!ret) return {};

    ObjData data;
    std::unordered_map<Vertex, unsigned int> uniqueVert;

    for (const auto& shape : shapes) {
        for (const auto& index : shape.mesh.indices) {
            Vertex vert;

            // Position (x, y, z)
            if (index.vertex_index >= 0) {
                vert.position = {
                    attrib.vertices[3 * index.vertex_index + 0],
                    attrib.vertices[3 * index.vertex_index + 1],
                    attrib.vertices[3 * index.vertex_index + 2],
                };
            }

            // TexCoord (u, v)
            if (index.texcoord_index >= 0) {
                vert.texCoord = {
                    attrib.texcoords[2 * index.texcoord_index + 0],
                    1.f - attrib.texcoords[2 * index.texcoord_index + 1],
                };
            }

            // Normals (nx, ny, nz)
            if (index.normal_index >= 0) {
                vert.normal = {
                    attrib.normals[3 * index.normal_index + 0],
                    attrib.normals[3 * index.normal_index + 1],
                    attrib.normals[3 * index.normal_index + 2],
                };
            }


            // Deduplication
            if (uniqueVert.count(vert) == 0) {
                uniqueVert[vert] = static_cast<unsigned int>(data.vertices.size());
                data.vertices.push_back(vert);
            }

            data.indices.push_back(uniqueVert[vert]);
        }
    }

    return data;
}

ptr<Model> ResourceManager::loadModel(const std::string& name, const fs::path& path, const std::string& shader, const std::string& texture) {
    const auto& shad = getShader(shader);
    const auto& tex = getTexture(texture);

    if (!shad) {
        log::error("ResourceManager::loadModel('{}'): Shader not found!", name);
        return nullptr;
    }

    auto objData = parseObjFile(path);

    const auto& model = models.emplace(
        name, std::make_shared<Model>(shad, objData, tex, phys::Transform())
    );

    if (!model.second) {
        log::error("ResourceManager::loadModel('{}'): Failed to emplace model!", name);
        return nullptr;
    }

    log::info("Loaded model '{}'", name);

    return model.first->second;
}
