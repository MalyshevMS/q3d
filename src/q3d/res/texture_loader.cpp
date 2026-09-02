#include <q3d/res/resources.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include <q3d/res/stb_image.h>
#include <q3d/gl/texture.hpp>

using namespace q3d;
using namespace gl;

ptr<Texture> ResourceManager::loadTexture(const std::string& name, const fs::path& path) {
    auto fullPath = fs::resolve(path);

    stbi_set_flip_vertically_on_load(true);

    int x, y, ch;
    Image data = stbi_load(
        fullPath.c_str(),
        &x, &y, &ch, 0
    );

    if (!data) {
        log::error("ResourceManager::loadTexture('{}'): stbi_load failed, corrupted data or unsupported format at '{}'!", name, path.string());
        return nullptr;
    }

    const auto& tex = textures.emplace(
        name, std::make_shared<gl::Texture>(data, x, y, ch)
    );

    if (!tex.second) {
        log::error("ResourceManager::loadTexture('{}'): Failed to emplace texture!", name);
        return nullptr;
    }

    log::info("Loaded texture '{}'", name);

    stbi_image_free(data);

    return tex.first->second;
}
