#pragma once

#include <string>
#include <string_view>
#include <unordered_map>
#include <q3d/gl/texture.hpp>
#include <q3d/gl/shader.hpp>
#include <q3d/res/ptr.hpp>

namespace q3d {
    namespace object {
        class Model;
    }

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

        // Maps

        TextureMap textures;
        ShaderMap shaders;
        ModelMap models;
    public:
        struct ObjData {
            std::vector<glm::vec3> positions;
            std::vector<glm::vec2> texCoords;
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

        ptr<gl::Shader> loadShader(std::string_view name, std::string_view vertex_path, std::string_view fragment_path);
        ptr<gl::Shader> getShader(std::string_view name);

        static ObjData parseObjFile(std::string_view fileContent);

        ptr<object::Model> loadModel(std::string_view name, std::string_view path, ptr<gl::Shader> shader, ptr<gl::Texture> texture = nullptr);
        ptr<object::Model> getModel(std::string_view name);
    };
}