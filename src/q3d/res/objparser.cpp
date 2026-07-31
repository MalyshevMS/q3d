#include <q3d/res/resources.hpp>
#define TINYOBJLOADER_IMPLEMENTATION
#include <q3d/res/tiny_obj_loader.h>
#include <q3d/log/log.hpp>

using namespace q3d;

Resources::ObjData Resources::parseObjFile(std::string_view path) {
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string warn, err;

    bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, path.data());

    if (!warn.empty()) {
        log::warn("Resources::parseObjFile('{}'): warning from loader: {}", path, warn);
    }

    if (!err.empty()) {
        log::warn("Resources::parseObjFile('{}'): error from loader: {}", path, err);
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
