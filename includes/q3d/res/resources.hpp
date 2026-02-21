#pragma once

#include <string>
#include <string_view>
#include <unordered_map>
#include <q3d/gl/texture.hpp>
#include <q3d/gl/shader.hpp>
#include <q3d/res/ptr.hpp>

namespace q3d {
    /// @warning SINGLETONE!!!
    class Resources {
    private:
        Resources(std::string_view exePath);
        static Resources* instance;

        std::string path;

        // Maps Typenames

        using TextureMap = std::unordered_map<std::string, ptr<gl::Texture>>;
        using ShaderMap = std::unordered_map<std::string, ptr<gl::Shader>>;

        // Maps

        TextureMap textures;
        ShaderMap shaders;
    public:
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
    };
}