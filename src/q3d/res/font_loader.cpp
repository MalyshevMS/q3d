#include <q3d/res/resources.hpp>
#include <q3d/ui/font.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <glad/glad.h>

using namespace q3d;
using namespace ui;

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

ptr<Font> ResourceManager::loadFont(const std::string& name, const fs::path& path, unsigned int size) {
    FT_Library ft;
    if (FT_Init_FreeType(&ft)) {
        log::error("ResourceManager::loadFont('{}'): FreeType failed to init!", name);
        return nullptr;
    }

    FT_Face face;
    if (FT_New_Face(ft, path.c_str(), 0, &face)) {
        log::error("ResourceManager::loadFont('{}'): failed to load font at '{}'!", name, path.string());
        return nullptr;
    }

    ui::CharMap charmap;

    FT_Set_Pixel_Sizes(face, 0, size);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    for (unsigned long c = 0; c < 128; c++) loadGlyph(face, charmap, c);

    // Cyrillic
    for (unsigned long c = 0x400; c <= 0x04FF; c++) loadGlyph(face, charmap, c);

    FT_Done_Face(face);
    FT_Done_FreeType(ft);


    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

    const auto& font= fonts.emplace(
        name, std::make_shared<Font>(charmap)
    );

    if (!font.second) {
        log::error("ResourceManager::loadFont('{}'): failed to emplace font!", name);
        return nullptr;
    }

    log::info("Loaded font '{}'", name);

    return font.first->second;
}

