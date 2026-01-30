#pragma once

namespace q3d {
    namespace gl {
        using Image = unsigned char*;

        class Texture {
        private:
            unsigned int id;
        public:
            Texture(const Image data, unsigned int width, unsigned int height, unsigned int channels);
            
            void bind();
            static void unbind();

            /// @warning shader program must have `uniform sampler2D u_texture`
            void use(class Shader& shader, const unsigned int unit = 0);

            // TODO: методы для настройки поведения текстуры
        };
    }
}