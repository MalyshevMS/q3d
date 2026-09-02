#pragma once
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/hash.hpp>

namespace q3d {

struct Vertex {
    glm::vec3 position;
    glm::vec2 texCoord;
    glm::vec3 normal;

    bool operator==(const Vertex& other) const {
        return position == other.position &&
               texCoord == other.texCoord &&
               normal   == other.normal;
    }
};

struct ObjData {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
};

} // namespace q3d

namespace std {

template<> struct hash<q3d::Vertex> {
    size_t operator()(q3d::Vertex const& vertex) const {
        size_t h1 = hash<glm::vec3>()(vertex.position);
        size_t h2 = hash<glm::vec2>()(vertex.texCoord);
        size_t h3 = hash<glm::vec3>()(vertex.normal);
        return h1 ^ (h2 << 1) ^ (h3 << 2);
    }
};

} // namespace std
