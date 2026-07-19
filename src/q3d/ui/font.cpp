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

Font::Font(std::map<wchar_t, Character> charmap)
: charmap(charmap) {}
