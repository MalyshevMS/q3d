#pragma once

#include <string>
#include <string_view>
#include <unordered_map>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/hash.hpp>
#include <q3d/core/material.hpp>
#include <q3d/gl/texture.hpp>
#include <q3d/gl/shader.hpp>
#include <q3d/ui/font.hpp>
#include <q3d/res/ptr.hpp>

namespace q3d {

namespace object {
class Model;
} // namespace object

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

/// @warning SINGLETONE!!!
class Resources {
private:
    Resources(std::string_view exePath);
    static Resources* instance;

    std::string path;

    // Maps Typenames

    using TextureMap = std::unordered_map<std::string, ptr<gl::Texture>>;
    using ShaderMap = std::unordered_map<std::string, ptr<gl::Shader>>;
    using ModelMap = std::unordered_map<std::string, ptr<object::Model>>;
    using FontMap = std::unordered_map<std::string, ptr<ui::Font>>;
    using MaterialMap = std::unordered_map<std::string, ptr<core::Material>>;

    // Maps

    TextureMap textures;
    ShaderMap shaders;
    ModelMap models;
    FontMap fonts;
    MaterialMap materials;
public:
    struct ObjData {
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
    };

    // some singletone...
    Resources(const Resources&) = delete;
    Resources& operator=(const Resources&) = delete;
    static Resources* getInstance(std::string_view exePath);

    std::string getExePath() { return path; }

    std::string readFile(std::string_view path);

    ptr<gl::Texture> loadTexture(std::string_view name, std::string_view path);
    ptr<gl::Texture> getTexture(std::string_view name);

    ptr<gl::Shader> loadShader(std::string_view name, std::string_view vertex_path, std::string_view fragment_path, std::string_view geometry_path = "");
    ptr<gl::Shader> getShader(std::string_view name);

    static ObjData parseObjFile(std::string_view path);

    ptr<object::Model> loadModel(std::string_view name, std::string_view path, ptr<gl::Shader> shader, ptr<gl::Texture> texture = nullptr);
    ptr<object::Model> getModel(std::string_view name);

    ptr<ui::Font> loadFont(std::string_view name, std::string_view path, unsigned int size);
    ptr<ui::Font> getFont(std::string_view name);

    ptr<core::Material> loadMaterial(std::string_view name, std::string_view path);
    ptr<core::Material> getMaterial(std::string_view name);
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

}
