#include <q3d/res/resources.hpp>
#include <q3d/log/log.hpp>
#include <fstream>
#include <sstream>
#define STB_IMAGE_IMPLEMENTATION
#include <q3d/res/stb_image.h>

q3d::Resources* q3d::Resources::instance = nullptr;

q3d::Resources::Resources(std::string_view exePath) {
    auto found = exePath.find_last_of("/\\");
    path = exePath.substr(0, ++found);
}

q3d::Resources *q3d::Resources::getInstance(std::string_view exePath) {
    if (instance == nullptr) instance = new Resources { std::move(exePath) };
    return instance;
}

std::string q3d::Resources::readFile(std::string_view path) {
    std::string fpath = this->path + std::string(path);

    std::ifstream ifs;
    ifs.open(fpath, std::ios::in | std::ios::binary);
    if (!ifs.is_open()) {
        log::warn("Failed to open file '{}'!", fpath);
        return {};
    }

    std::ostringstream oss;
    oss << ifs.rdbuf();

    return oss.str();
}

q3d::ptr<q3d::gl::Texture> q3d::Resources::loadTexture(std::string_view name, std::string_view path) {
    stbi_set_flip_vertically_on_load(true);
    int x, y, ch;
    unsigned char* data = stbi_load(
        (getExePath() + path.data()).c_str(),
        &x, &y, &ch, 0
    );

    if (!data) return nullptr;

    const auto& tex = textures.emplace<std::string, ptr<gl::Texture>>(
        name.data(), std::make_shared<gl::Texture>(data, x, y, ch)
    );

    if (!tex.second) return nullptr;

    stbi_image_free(data);
    return tex.first->second;
}

q3d::ptr<q3d::gl::Texture> q3d::Resources::getTexture(std::string_view name) {
    auto it = textures.find(name.data());
    if (it == textures.end()) return nullptr;
    return it->second;
}