#pragma once

#include <string>
#include <unordered_map>
#include <q3d/res/fs.hpp>
#include <q3d/res/ptr.hpp>
#include <q3d/log/log.hpp>

// Forward declarations
namespace q3d {

namespace gl {
    class Texture;
    class Shader;
}

namespace object {
    class Model;
}

namespace ui {
    class Font;
}

namespace core {
    struct Material;
}

}

namespace q3d {

class ResourceManager {
private:
    std::unordered_map<std::string, ptr<gl::Texture>>    textures;
    std::unordered_map<std::string, ptr<gl::Shader>>     shaders;
    std::unordered_map<std::string, ptr<object::Model>>  models;
    std::unordered_map<std::string, ptr<ui::Font>>       fonts;
    std::unordered_map<std::string, ptr<core::Material>> materials;
public:
    ResourceManager() = default;
    ~ResourceManager() = default;

    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;

    ResourceManager(ResourceManager&&) = default;
    ResourceManager& operator=(ResourceManager&&) = default;

    // Loaders
    ptr<gl::Texture>    loadTexture(const std::string& name, const fs::path& path);
    ptr<gl::Shader>     loadShader(const std::string& name, const fs::path& vert, const fs::path& frag, const fs::path& geom = "");
    ptr<object::Model>  loadModel(const std::string& name, const fs::path& path, const std::string& shader, const std::string& texture);
    ptr<ui::Font>       loadFont(const std::string& name, const fs::path& path, unsigned int size);
    ptr<core::Material> loadMaterial(const std::string& name, const fs::path& path);

    // Getters
    ptr<gl::Texture>    getTexture(const std::string& name) const;
    ptr<gl::Shader>     getShader(const std::string& name) const;
    ptr<object::Model>  getModel(const std::string& name) const;
    ptr<ui::Font>       getFont(const std::string& name) const;
    ptr<core::Material> getMaterial(const std::string& name) const;
};

}
