#pragma once

#include <q3d/res/ptr.hpp>
#include <glm/vec2.hpp>
#include <map>
#include <q3d/gl/texture.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H

namespace q3d::ui {

struct Character {
    ptr<gl::Texture> texture;
    glm::ivec2 size;
    glm::ivec2 bearing;
    unsigned int advance;
};

using CharMap = std::map<wchar_t, Character>;

class Font {
private:
    CharMap charmap;

    void loadGlyph(FT_Face& face, unsigned long c);
public:
    Font(CharMap charmap);

    const Character& getc(wchar_t c) const;
};

} // namespace q3d::ui
