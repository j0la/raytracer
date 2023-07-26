#include <cmath>
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