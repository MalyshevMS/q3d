#include <q3d/res/resources.hpp>

using namespace q3d;
using namespace vfs;

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

void ResourceManager::clear() {
    models.clear();
    fonts.clear();
    materials.clear();
    shaders.clear();
    textures.clear();
}

struct Asset {
    std::string name;
    FileBuffer buffer;
};

static std::vector<Asset> loadAssets(const VFS& vfs, const std::string& classname) {
    auto files = vfs.listFiles();
    std::vector<Asset> result;

    for (const auto& f : files) {
        auto path = fs::path(f);

        if (path.parent_path() != classname) continue;

        auto buffer = vfs.readFile(path.string());
        auto name = path.stem().string();

        if (!buffer) {
            log::warn("loadAssets('{}'): Warning, failed to read buffer from '{}'", vfs.getName(), path.string());
            continue;
        }

        result.emplace_back(name, *buffer);
    }

    return result;
}

void ResourceManager::load(const fs::path& path) {
    auto filepath = fs::resolve(path);

    VFS vfs;
    if (!vfs.openArchive(filepath)) {
        log::error("ResourceManager::load('{}'): Failed to open archive", filepath.string());
        return;
    } else {
        log::info("Loading assets from '{}'...", path.string());
    }

    loadTextures(vfs);
}

void ResourceManager::loadTextures(const VFS& vfs) {
    auto assets = loadAssets(vfs, "textures");

    for (const auto& [name, buffer] : assets) {
        auto ptr = loader::texture(buffer.data);

        const auto& tex = textures.emplace(
            name, std::move(ptr)
        );

        if (!tex.second) {
            log::error("ResourceManager::loadTextures('{}'): Failed to emplace texture '{}'!", vfs.getName(), name);
            continue;
        }

        log::info("Loaded texture '{}'", name);
    }
}

