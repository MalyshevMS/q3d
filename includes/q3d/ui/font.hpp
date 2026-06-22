#pragma once

#include <q3d/res/ptr.hpp>
#include <glm/vec2.hpp>
#include <map>
#include <string_view>
#include <q3d/gl/texture.hpp>

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
            std::map<char, Character> charmap;
        public:
            Font(std::string_view path, unsigned int size);

            const Character& getc(char c) const;
        };
    }
}
