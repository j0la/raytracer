#ifndef GRAPHICS_H_
#define GRAPHICS_H_

struct Color {
    float r, g, b; // range: [0, 1]
};

struct Material {
    Color od, os; // diffuse and specular color
    float ka, kd, ks; // ambient, diffuse, specular reflectivity [0, 1]
    float n; // specular falloff
    float a; // opacity [0, 1]
    float i; // refractive index
};

// RETURNS: color scaled by s
Color operator*(const Color& c, float s);
Color operator/(const Color& c, float s);

// RETURNS: combined color components
Color operator+(const Color& c1, const Color& c2);
Color operator-(const Color& c1, const Color& c2);
Color operator*(const Color& c1, const Color& c2);
Color operator/(const Color& c1, const Color& c2);

// RETURNS: value restricted to the range [min, max]
float clamp(float f, float min, float max);

// RETURNS: color with components restricted to the range [min, max]
Color clamp(const Color& c, float min, float max);

#endif