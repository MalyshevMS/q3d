#pragma once

#include <q3d/gl/vbo.hpp>

namespace q3d {
    namespace gl {
        class Ibo {
        private:
            unsigned int id;
            unsigned int count;
        public:
            Ibo(const void* data, const unsigned int count, const Vbo::Mode mode = Vbo::Mode::Static);
            ~Ibo();

            void bind();
            static void unbind();

            unsigned int getCount() { return count; }
        };
    }
}