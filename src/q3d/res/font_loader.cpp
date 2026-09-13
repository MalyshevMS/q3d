#include <q3d/res/loaders.hpp>
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

ptr<Font> loader::font(bytes raw, unsigned int size) {
    FT_Library ft;
    if (FT_Init_FreeType(&ft)) {
        log::error("loader::font(): FreeType failed to init");
        return nullptr;
    }

    FT_Face face;
    if (FT_New_Memory_Face(ft, raw.data(), raw.size(), 0, &face)) {
        log::error("loader::font(): failed to load font");
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

    return std::make_shared<Font>(charmap);
}

ptr<Font> ResourceManager::loadFont(const std::string& name, const fs::path& path, unsigned int size) {
    auto f = loader::font(fs::readFileBytes(path), size);

    const auto& font = fonts.emplace(
        name, std::move(f)
    );

    if (!font.second) {
        log::error("ResourceManager::loadFont('{}'): failed to emplace font!", name);
        return nullptr;
    }

    log::info("Loaded font '{}'", name);

    return font.first->second;
}

