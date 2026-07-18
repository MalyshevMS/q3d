#include <q3d/ui/font.hpp>
#include <q3d/log/log.hpp>
#include <glad/glad.h>
#include <ft2build.h>
#include FT_FREETYPE_H

using namespace q3d;
using namespace ui;

const Character& Font::getc(wchar_t c) const {
    auto it = charmap.find(c);
    if (it != charmap.end()) {
        return it->second;
    }

    return charmap.at(' ');
}

void Font::loadGlyph(FT_Face& face, unsigned long c) {
    if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
        log::error("FreeType: failed to load glyph '{}'", c);
        return;
    }

    auto textTex = std::make_shared<gl::Texture>(
        face->glyph->bitmap.buffer,
        face->glyph->bitmap.width,
        face->glyph->bitmap.rows,
        1
    );

    textTex->setFilter(gl::Texture::Filter::Linear, gl::Texture::Filter::Linear);
    textTex->wrapMode(gl::Texture::WrapMode::ClampToEdge, gl::Texture::WrapMode::ClampToEdge);

    Character character = {
        textTex,
        glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
        glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
        static_cast<unsigned int>(face->glyph->advance.x)
    };
    charmap.insert({c, character});
}

Font::Font(std::map<wchar_t, Character> charmap)
: charmap(charmap) {}
