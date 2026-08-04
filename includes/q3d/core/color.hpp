#pragma once

#include <cstdint>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

namespace q3d::core {

using byte = unsigned char;

struct Color {
    union {
        struct {
            float r, g, b, a;
        };

        float raw[4];
    };

    Color() : r(0.f), g(0.f), b(0.f), a(0.f) {}

    Color(byte r, byte g, byte b, byte a = 255)
     : r(r / 255.f), g(g / 255.f), b(b / 255.f), a(a / 255.f) {}

    Color(float r, float g, float b, float a = 1.f)
     : r(r), g(g), b(b), a(a) {}

    Color(uint32_t hex)
     : r(((hex >> 24) & 0xFF) / 255.f),
       g(((hex >> 16) & 0xFF) / 255.f),
       b(((hex >>  8) & 0xFF) / 255.f),
       a(((hex >>  0) & 0xFF) / 255.f)
    {}

    glm::vec4 vec4() const {
        return glm::vec4(r, g, b, a);
    }

    glm::vec3 vec3() const {
        return glm::vec3(r, g, b);
    }

    static const Color Red;
    static const Color Green;
    static const Color Blue;

    static const Color Yellow;
    static const Color Magenta;
    static const Color Cyan;

    static const Color Black;
    static const Color White;
    static const Color Gray;
    static const Color Transparent;
};

} // namespace q3d::core
