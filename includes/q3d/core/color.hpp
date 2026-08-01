#pragma once

#include <cstdint>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

namespace q3d::core {

using byte = unsigned char;

class Color {
private:
    float color[4]; // GL-formated color [0..1] (4-components)
public:
    float& r = color[0];
    float& g = color[1];
    float& b = color[2];
    float& a = color[3];

    Color();
    Color(byte r, byte g, byte b, byte a = (byte)255);
    Color(float r, float g, float b, float a = 1.f);
    Color(uint64_t color);

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
