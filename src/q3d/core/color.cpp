#include <q3d/core/color.hpp>

using namespace q3d::core;

inline const Color Color::Red =             {1.f, 0.f, 0.f, 1.f};
inline const Color Color::Green =           {0.f, 1.f, 0.f, 1.f};
inline const Color Color::Blue =            {0.f, 0.f, 1.f, 1.f};

inline const Color Color::Yellow =          {1.f, 1.f, 0.f, 1.f};
inline const Color Color::Magenta =         {1.f, 0.f, 1.f, 1.f};
inline const Color Color::Cyan =            {0.f, 1.f, 1.f, 1.f};

inline const Color Color::Black =           {0.f, 0.f, 0.f, 1.f};
inline const Color Color::White =           {1.f, 1.f, 1.f, 1.f};
inline const Color Color::Transparent =     {0.f, 0.f, 0.f, 0.f};

Color::Color() {
    r = 0.f;
    g = 0.f;
    b = 0.f;
    a = 0.f;
}

Color::Color(byte r, byte g, byte b, byte a) {
    this->r = r / 255.f;
    this->g = g / 255.f;
    this->b = b / 255.f;
    this->a = a / 255.f;
}

Color::Color(float r, float g, float b, float a) {
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}

Color::Color(uint64_t color) {
    r = (color & 0xFF'00'00'00) >> 6;
    g = (color & 0x00'FF'00'00) >> 4;
    b = (color & 0x00'00'FF'00) >> 2;
    a = (color & 0x00'00'00'FF) >> 0;
}