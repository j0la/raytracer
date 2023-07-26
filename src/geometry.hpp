#ifndef GEOMETRY_H_
#define GEOMETRY_H_

#include "graphics.hpp"

struct Vector {
    float x, y, z;
};

struct Ray {
    Vector origin;
    Vector dir;
};

struct Sphere {
    Vector origin;
    float radius;
    Material& material;
};

struct PointLight {
    Vector origin;
    Color color;
};

#endif