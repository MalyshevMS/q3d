#pragma once

#include <stdint.h>

namespace q3d {
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

        static const Color Red;
        static const Color Green;
        static const Color Blue;

        static const Color Yellow;
        static const Color Magenta;
        static const Color Cyan;

        static const Color Black;
        static const Color White;
        static const Color Transparent;
    };
}