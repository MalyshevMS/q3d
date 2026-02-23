#include <q3d/res/resources.hpp>
#include <q3d/obj/3d/model.hpp>
#include <q3d/log/log.hpp>
#include <fstream>
#include <sstream>
#define STB_IMAGE_IMPLEMENTATION
#include <q3d/res/stb_image.h>

using namespace q3d;

Resources* Resources::instance = nullptr;

Resources::Resources(std::string_view exePath) {
    auto found = exePath.find_last_of("/\\");
    path = exePath.substr(0, ++found);
}

Resources *Resources::getInstance(std::string_view exePath) {
    if (instance == nullptr) instance = new Resources { std::move(exePath) };
    return instance;
}

std::string Resources::readFile(std::string_view path) {
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

ptr<gl::Texture> Resources::loadTexture(std::string_view name, std::string_view path) {
    stbi_set_flip_vertically_on_load(true);
    int x, y, ch;
    unsigned char* data = stbi_load(
        (getExePath() + path.data()).c_str(),
        &x, &y, &ch, 0
    );

    if (!data) {
        log::error("Resources::loadTexture('{}'): stbi_load failed, data corrupted!", name, path);
        return nullptr;
    }

    const auto& tex = textures.emplace<std::string, ptr<gl::Texture>>(
        name.data(), std::make_shared<gl::Texture>(data, x, y, ch)
    );

    if (!tex.second) {
        log::error("Resources::loadTexture('{}'): Failed to emplace texture!", name);
        return nullptr;
    }

    log::info("Loaded texture '{}'", name);

    stbi_image_free(data);
    return tex.first->second;
}

ptr<gl::Texture> Resources::getTexture(std::string_view name) {
    auto it = textures.find(name.data());
    if (it == textures.end()) return nullptr;
    return it->second;
}

ptr<gl::Shader> Resources::loadShader(std::string_view name, std::string_view vertex_path, std::string_view fragment_path) {
    auto shader = std::make_shared<gl::Shader>();

    auto vert_src = readFile(vertex_path);
    auto frag_src = readFile(fragment_path);

    if (vert_src.empty()) {
        log::error("Resources::loadShader('{}'): Vertex shader is empty!", name);
        return nullptr;
    }

    if (frag_src.empty()) {
        log::error("Resources::loadShader('{}'): Fragment shader is empty!", name);
        return nullptr;
    }

    shader->attach(vert_src, gl::Shader::Type::Vertex);
    shader->attach(frag_src, gl::Shader::Type::Fragment);
    shader->link();

    if (!shader->isLinked()) {
        log::error("Resources::loadShader('{}'): Shader is not linked!", name);
        return nullptr;
    }

    const auto& shader_el = shaders.emplace<std::string, ptr<gl::Shader>>(
        name.data(), std::move(shader)
    );

    if (!shader_el.second) {
        log::error("Resources::loadShader('{}'): Failed to emplace shader!", name);
    }

    log::info("Loaded shader '{}'", name);
    return shader_el.first->second;
}

ptr<gl::Shader> Resources::getShader(std::string_view name) {
    auto it = shaders.find(name.data());
    if (it == shaders.end()) return nullptr;
    return it->second;
}

ptr<object::Model> Resources::loadModel(std::string_view name, std::string_view path, ptr<gl::Shader> shader, ptr<gl::Texture> texture) {
    if (!shader) {
        log::error("Resources::loadModel('{}'): Shader is nullptr!", name);
        return nullptr;
    }

    auto fileContent = readFile(path);
    if (fileContent.empty()) {
        log::error("Resources::loadModel('{}'): Failed to read file '{}'!", name, path);
        return nullptr;
    }
    
    auto objData = parseObjFile(fileContent);
    const auto& model_el = models.emplace<std::string, ptr<object::Model>>(
        name.data(), std::make_shared<object::Model>(shader, objData, phys::Transform(), texture)
    );

    if (!model_el.second) {
        log::error("Resources::loadModel('{}'): Failed to emplace model!", name);
        return nullptr;
    }

    log::info("Loaded model '{}'", name);
    return model_el.first->second;
}

ptr<object::Model> Resources::getModel(std::string_view name) {
    auto it = models.find(name.data());
    if (it == models.end()) return nullptr;
    return it->second;
}