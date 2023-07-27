#include <cmath>
#include <algorithm>
#include "geometry.hpp"

const double pi = std::acos(-1);

float v_length(const Vector& v) {
    return sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2));
}

Vector v_norm(const Vector& v) {
    float len = v_length(v);
    Vector unit_vector = { v.x / len, v.y / len, v.z / len };
    return unit_vector;
}

Vector v_cross(const Vector& v1, const Vector& v2) {
    return {
        v1.y * v2.z - v1.z * v2.y,
        v1.z * v2.x - v1.x * v2.z,
        v1.x * v2.y - v1.y * v2.x
    };
}

Vector v_project(const Vector& v1, const Vector& v2) {
    float s = (v1 * v2) / (v2 * v2);
    return v2 * s;
}

float operator*(const Vector& v1, const Vector& v2) {
    return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}

Vector operator+(const Vector& v1, const Vector& v2) {
    return {
        v1.x + v2.x,
        v1.y + v2.y,
        v1.z + v2.z
    };
}

Vector operator-(const Vector& v1, const Vector& v2) {
    return {
        v1.x - v2.x,
        v1.y - v2.y,
        v1.z - v2.z
    };
}

Vector operator*(const Vector& v, float s) {
    return { v.x * s, v.y * s, v.z * s };
}

Vector operator/(const Vector& v, float s) {
    return { v.x / s, v.y / s, v.z / s };
}

float intersect(Ray& ray, Sphere& sphere) {
    // ray equation: (x0, y0, z0) + t*(xd, yd, zd)
    // sphere equation: (x - xc)^2 + (y - yc)^2 + (z - zc)^2 = r^2
    float a = 1;
    float b = 2 * (ray.dir.x * (ray.origin.x - sphere.origin.x) + ray.dir.y * (ray.origin.y - sphere.origin.y) + ray.dir.z * (ray.origin.z - sphere.origin.z));
    float c = pow(ray.origin.x - sphere.origin.x, 2) + pow(ray.origin.y - sphere.origin.y, 2) + pow(ray.origin.z - sphere.origin.z, 2) - pow(sphere.radius, 2);
 
    float disc = pow(b, 2) - (4 * a * c);
    
    if (disc > 0) {
        // 2 intersections (pierce)
        float t1 = (-b + sqrtf(disc)) / (2 * a);
        float t2 = (-b - sqrtf(disc)) / (2 * a);
        // choose closer forward intersection
        return t1 < 0 && t2 < 0 ? -1
            : t1 < 0 ? t2
            : t2 < 0 ? t1
            : std::min(t1, t2);
    } else if (disc == 0) {
        // 1 intersection (graze)
        return -b / (2 * a);
    } else {
        // 0 intersections (miss)
        return -1;
    }
}