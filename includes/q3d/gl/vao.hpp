#pragma once

#include <q3d/gl/vbo.hpp>
#include <q3d/gl/ibo.hpp>

namespace q3d {
    namespace gl {
        class Vao {
        private:
            unsigned int id;
            unsigned int elCount = 0;
            unsigned int vertexCount = 0;
            unsigned int indCount = 0;
        public:
            Vao();
            ~Vao();

            void bind();
            static void unbind();

            void addVbo(Vbo& vbo);
            void setIbo(Ibo& ibo);

            unsigned int getIndeciesCount() const { return indCount; }

            // TODO: инкапсулировать GL-методы рисования
            void draw(unsigned int method = 0x0004); // GL_TRIANGLES by default
        };
    }
}