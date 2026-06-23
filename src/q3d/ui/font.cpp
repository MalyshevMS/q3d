#include <q3d/ui/font.hpp>
#include <q3d/log/log.hpp>
#include <glad/glad.h>
#include <ft2build.h>
#include FT_FREETYPE_H

using namespace q3d::ui;

const Character& Font::getc(char c) const {
    auto it = charmap.find(c);
    if (it != charmap.end()) {
        return it->second;
    }

    return charmap.at(' ');
}

Font::Font(std::string_view path, unsigned int size) {
    FT_Library ft;
    if (FT_Init_FreeType(&ft)) {
        log::error("FreeType: failed to init");
        return;
    }

    FT_Face face;
    if (FT_New_Face(ft, path.data(), 0, &face)) {
        log::error("FreeType: failed to load font at '{}'", path);
        FT_Done_FreeType(ft);
        return;
    }

    FT_Set_Pixel_Sizes(face, 0, size);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    for (unsigned char c = 0; c < 128; c++) {
        if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
            log::error("FreeType: failed to load glyph '{}'", c);
            continue;
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

    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    log::info("FreeType: loaded font '{}'", path);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
}
