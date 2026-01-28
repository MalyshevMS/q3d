#pragma once

#include <vector>

namespace q3d {
    namespace gl {
        namespace buffer {
            enum class DataType {
                float1,   int1,
                float2,   int2,
                float3,   int3,
                float4,   int4,
            };

            unsigned int getCount(DataType type);
            unsigned int getSize(DataType type);
            unsigned int getGlType(DataType type);

            struct Element {
                DataType type;

                unsigned int glType;
                unsigned int count;
                unsigned int size;
                unsigned int offset;

                Element(DataType type)
                 : type(type),
                   glType(getGlType(type)),
                   count(getCount(type)),
                   size(getSize(type)),
                   offset(0u)
                {}
            };

            class Layout {
            private:
                std::vector<Element> elements;
                unsigned int stride;
            public:
                Layout(std::initializer_list<Element> lst);

                const std::vector<Element>& getElements() const;
                unsigned int getStride() const { return stride; }
            };
        }

        class Vbo {
        private:
            unsigned int id;
            buffer::Layout layout;
            unsigned int vertexCount = 0;
        public:
            enum class Mode {
                Static, Dynamic, Stream
            };
            
            static unsigned int toGlMode(Mode mode);

            Vbo(const void* data, const unsigned int size, buffer::Layout layout, Mode mode = Mode::Static);
            ~Vbo();

            void bind();
            static void unbind();

            buffer::Layout getLayout() { return layout; }
            unsigned int getVertexCount() const { return vertexCount; }
        };
    }
}