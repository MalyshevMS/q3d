#pragma once

namespace q3d {
    namespace gl {
        using Image = unsigned char*;

        class Texture {
        private:
            unsigned int id;
        public:
            enum class WrapMode {
                ClampToEdge,
                ClampToBorder,
                MirroredRepeat,
                Repeat,
                MirrorClampToEdge
            };

            enum class Filter {
                Nearest, Linear,

                LinearMMLinear,
                LinearMMNearest,
                NearestMMLinear,
                NearestMMNearest,
            };

            Texture(const Image data, unsigned int width, unsigned int height, unsigned int channels);
            
            void bind();
            static void unbind();

            /// @warning shader program must have `uniform sampler2D u_texture`
            void use(class Shader& shader, const unsigned int unit = 0);

            void wrapMode(WrapMode wrapS, WrapMode wrapT);
            void setFilter(Filter min, Filter mag);
        };
    }
}