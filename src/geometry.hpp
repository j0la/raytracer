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

// RETURNS: length of v
float v_length(const Vector& v);

// RETURNS: unit vector in the direction of v
Vector v_norm(const Vector& v);

// RETURNS: cross product of v1 and v2
Vector v_cross(const Vector& v1, const Vector& v2);

// RETURNS: orthogonal projection of v1 onto v2
Vector v_project(const Vector& v1, const Vector& v2);

// RETURNS: dot product of v1 and v2
float operator*(const Vector& v1, const Vector& v2);

// RETURNS: combined vector components
Vector operator+(const Vector& v1, const Vector& v2);
Vector operator-(const Vector& v1, const Vector& v2);

// RETURNS: v scaled by s
Vector operator*(const Vector& v, float s);
Vector operator/(const Vector& v, float s);

#endif