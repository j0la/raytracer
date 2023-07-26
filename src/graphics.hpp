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

#endif