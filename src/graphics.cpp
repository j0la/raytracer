#include "graphics.hpp"

Color operator*(const Color& c, float s) {
    return { c.r * s, c.g * s, c.b * s };
}

Color operator/(const Color& c, float s) {
    return { c.r / s, c.g / s, c.b / s };
}

Color operator+(const Color& c1, const Color& c2) {
    return { c1.r + c2.r, c1.g + c2.g, c1.b + c2.b };
}

Color operator-(const Color& c1, const Color& c2) {
    return { c1.r - c2.r, c1.g - c2.g, c1.b - c2.b };
}

Color operator*(const Color& c1, const Color& c2) {
    return { c1.r * c2.r, c1.g * c2.g, c1.b * c2.b };
}

Color operator/(const Color& c1, const Color& c2) {
    return { c1.r / c2.r, c1.g / c2.g, c1.b / c2.b };
}

float clamp(float f, float min, float max) {
    return f < min ? min : (f > max ? max : f);
}

Color clamp(const Color& c, float min, float max) {
    return {
        clamp(c.r, min, max),
        clamp(c.g, min, max),
        clamp(c.b, min, max),
    };
}