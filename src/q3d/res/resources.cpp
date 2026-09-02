#include <q3d/res/resources.hpp>

using namespace q3d;


ptr<gl::Texture> ResourceManager::getTexture(const std::string& name) const {
    auto it = textures.find(name);
    return it != textures.end() ? it->second : nullptr;
}

ptr<gl::Shader> ResourceManager::getShader(const std::string& name) const {
    auto it = shaders.find(name);
    return it != shaders.end() ? it->second : nullptr;
}

ptr<object::Model> ResourceManager::getModel(const std::string& name) const {
    auto it = models.find(name);
    return it != models.end() ? it->second : nullptr;
}

ptr<ui::Font> ResourceManager::getFont(const std::string& name) const {
    auto it = fonts.find(name);
    return it != fonts.end() ? it->second : nullptr;
}

ptr<core::Material> ResourceManager::getMaterial(const std::string& name) const {
    auto it = materials.find(name);
    return it != materials.end() ? it->second : nullptr;
}
