#pragma once

#include <q3d/gl/vbo.hpp>
#include <q3d/gl/ibo.hpp>

namespace q3d::gl {

enum class DrawMethod {
    Points,
    Lines,
    LineStrip,
    LineLoop,
    Triangles,
    TriangleStrip,
    TriangleFan,
    Patches
};

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

    void draw(DrawMethod method = DrawMethod::Triangles);
};

} // namespace q3d::core
