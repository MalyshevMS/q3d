#pragma once

#include <q3d/res/ptr.hpp>
#include <glm/vec2.hpp>
#include <map>
#include <q3d/gl/texture.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H

namespace q3d {
    namespace ui {
        struct Character {
            ptr<gl::Texture> texture;
            glm::ivec2 size;
            glm::ivec2 bearing;
            unsigned int advance;
        };

        class Font {
        private:
            std::map<wchar_t, Character> charmap;

            void loadGlyph(FT_Face& face, unsigned long c);
        public:
            Font(std::string_view path, unsigned int size);

            const Character& getc(wchar_t c) const;
        };
    }
}
