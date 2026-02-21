#include <q3d/gl/gl.hpp>
#include <q3d/core/color.hpp>
#include <glad/glad.h>

using namespace q3d;

void gl::clear() {
    glClear(GL_COLOR_BUFFER_BIT);
}

void gl::clearColor(core::Color color) {
    glClearColor(color.r, color.g, color.b, color.a);
}

GLenum featureToGL(gl::feature feat) {
    using enum gl::feature;

    switch (feat) {
        case cullFace: return GL_CULL_FACE;
    }

    return 0;
}

void gl::enable(feature feat) {
    glEnable(featureToGL(feat));
}

void gl::disable(feature feat) {
    glDisable(featureToGL(feat));
}