#include <glm/ext/vector_int2.hpp>
#include <q3d/gl/texture.hpp>
#include <q3d/ui/font.hpp>
#include <glad/glad.h>
#include <q3d/res/resources.hpp>
#include <q3d/obj/model.hpp>
#include <q3d/log/log.hpp>
#include <memory>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string_view>
#define STB_IMAGE_IMPLEMENTATION
#include <q3d/res/stb_image.h>
#include <nlohmann/json.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H

using namespace q3d;
using json = nlohmann::json;

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
        log::warn("Resources::readFile('{}'): Failed to open file '{}'!", path, fpath);
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

    const auto& tex = textures.emplace(
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

ptr<gl::Shader> Resources::loadShader(std::string_view name, std::string_view vertex_path, std::string_view fragment_path, std::string_view geometry_path) {
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

    if (!geometry_path.empty()) {
        auto geom_src = readFile(geometry_path);

        if (geom_src.empty()) {
            log::error("Resources::loadShader('{}'): Geometry shader is empty!", name);
            return nullptr;
        }

        shader->attach(geom_src, gl::Shader::Type::Geometry);
    }

    shader->link();

    if (!shader->isLinked()) {
        log::error("Resources::loadShader('{}'): Shader is not linked!", name);
        return nullptr;
    }

    const auto& shader_el = shaders.emplace(
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

    auto objData = parseObjFile(path);
    const auto& model_el = models.emplace(
        name.data(), std::make_shared<object::Model>(shader, objData, texture, phys::Transform())
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

void loadGlyph(FT_Face& face, ui::CharMap& charmap, unsigned long c) {
    if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
        log::error("loadGlyph('{}'): failed to load glyph!", c);
        return;
    }

    auto tex = std::make_shared<gl::Texture>(
        face->glyph->bitmap.buffer,
        face->glyph->bitmap.width,
        face->glyph->bitmap.rows,
        1
    );

    tex->setFilter(gl::Texture::Filter::Linear, gl::Texture::Filter::Linear);
    tex->wrapMode(gl::Texture::WrapMode::ClampToEdge, gl::Texture::WrapMode::ClampToEdge);

    ui::Character ch = {
        tex,
        glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
        glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
        static_cast<unsigned int>(face->glyph->advance.x)
    };

    charmap.insert({c, ch});
}

ptr<ui::Font> Resources::loadFont(std::string_view name, std::string_view path, unsigned int size) {
    FT_Library ft;
    if (FT_Init_FreeType(&ft)) {
        log::error("Resources::loadFont('{}'): FreeType failed to init!", name);
        return nullptr;
    }

    FT_Face face;
    if (FT_New_Face(ft, path.data(), 0, &face)) {
        log::error("Resources::loadFont('{}'): failed to load font at '{}'!", name, path);
        return nullptr;
    }

    ui::CharMap charmap;

    FT_Set_Pixel_Sizes(face, 0, size);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    for (unsigned long c = 0; c < 128; c++) loadGlyph(face, charmap, c);

    // Cyrilic
    for (unsigned long c = 0x400; c <= 0x04FF; c++) loadGlyph(face, charmap, c);

    FT_Done_Face(face);
    FT_Done_FreeType(ft);


    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

    const auto& font_el = fonts.emplace(
        name, std::make_shared<ui::Font>(charmap)
    );

    if (!font_el.second) {
        log::error("Resources::loadFont('{}'): failed to emplace font!", name);
        return nullptr;
    }

    log::info("Loaded font '{}'", name);

    return font_el.first->second;
}

ptr<ui::Font> Resources::getFont(std::string_view name) {
    auto it = fonts.find(name.data());
    if (it == fonts.end()) return nullptr;
    return it->second;
}

ptr<core::Material> Resources::loadMaterial(std::string_view name, std::string_view path) {
    auto content = readFile(path);
    json j = json::parse(content);

    auto mat = std::make_shared<core::Material>();

    mat->ambient.r = j["ambient"][0];
    mat->ambient.g = j["ambient"][1];
    mat->ambient.b = j["ambient"][2];

    mat->diffuse.r = j["diffuse"][0];
    mat->diffuse.g = j["diffuse"][1];
    mat->diffuse.b = j["diffuse"][2];

    mat->specular.r = j["specular"][0];
    mat->specular.g = j["specular"][1];
    mat->specular.b = j["specular"][2];

    mat->shininess = j["shininess"];

    const auto& mat_el = materials.emplace(
        name, mat
    );

    if (!mat_el.second) {
        log::error("Resources::loadMaterial('{}'): failed to emplace material", name);
        return nullptr;
    }

    log::info("Loaded material '{}'", name);

    return mat_el.first->second;
}

ptr<core::Material> Resources::getMaterial(std::string_view name) {
    auto it = materials.find(name.data());
    if (it == materials.end()) return nullptr;
    return it->second;
}
