#ifndef RENDER_H_
#define RENDER_H_

#include <string>
#include "scene.hpp"

#define MIN_IXN_DISTANCE 0.1 // offset to avoid self-intersections
#define MAX_RAY_DEPTH 5 // reflection recursion depth

void render(Scene& scene, std::vector<std::vector<Color>>& pixels);
Color cast_ray(Scene& scene, Ray& ray, float ni, int depth);
void write_ppm(std::vector<std::vector<Color>>& pixels, std::string path);

#endif