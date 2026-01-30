#include <q3d/system/color.hpp>


inline const q3d::Color q3d::Color::Red =             {1.f, 0.f, 0.f, 1.f};
inline const q3d::Color q3d::Color::Green =           {0.f, 1.f, 0.f, 1.f};
inline const q3d::Color q3d::Color::Blue =            {0.f, 0.f, 1.f, 1.f};

inline const q3d::Color q3d::Color::Yellow =          {1.f, 1.f, 0.f, 1.f};
inline const q3d::Color q3d::Color::Magenta =         {1.f, 0.f, 1.f, 1.f};
inline const q3d::Color q3d::Color::Cyan =            {0.f, 1.f, 1.f, 1.f};

inline const q3d::Color q3d::Color::Black =           {0.f, 0.f, 0.f, 1.f};
inline const q3d::Color q3d::Color::White =           {1.f, 1.f, 1.f, 1.f};
inline const q3d::Color q3d::Color::Transparent =     {0.f, 0.f, 0.f, 0.f};

q3d::Color::Color() {
    r = 0.f;
    g = 0.f;
    b = 0.f;
    a = 0.f;
}

q3d::Color::Color(byte r, byte g, byte b, byte a) {
    this->r = r / 255.f;
    this->g = g / 255.f;
    this->b = b / 255.f;
    this->a = a / 255.f;
}

q3d::Color::Color(float r, float g, float b, float a) {
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}

q3d::Color::Color(uint64_t color) {
    r = (color & 0xFF'00'00'00) >> 6;
    g = (color & 0x00'FF'00'00) >> 4;
    b = (color & 0x00'00'FF'00) >> 2;
    a = (color & 0x00'00'00'FF) >> 0;
}