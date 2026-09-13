#include <q3d/res/loaders.hpp>
#include <q3d/res/resources.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include <q3d/res/stb_image.h>
#include <q3d/gl/texture.hpp>

using namespace q3d;
using namespace gl;

ptr<Texture> loader::texture(bytes raw) {
    stbi_set_flip_vertically_on_load(true);

    int x, y, ch;
    Image data = stbi_load_from_memory(
        raw.data(), raw.size(),
        &x, &y, &ch, 0
    );

    if (!data) {
        log::error("loader::texture(): stbi_load failed, corrupted data or unsupported format");
        return nullptr;
    }

    return std::make_shared<Texture>(data, x, y, ch);
}

ptr<Texture> ResourceManager::loadTexture(const std::string& name, const fs::path& path) {
    auto texture = loader::texture(fs::readFileBytes(path));

    const auto& tex = textures.emplace(
        name, std::move(texture)
    );

    if (!tex.second) {
        log::error("ResourceManager::loadTexture('{}'): Failed to emplace texture!", name);
        return nullptr;
    }

    log::info("Loaded texture '{}'", name);

    return tex.first->second;
}
