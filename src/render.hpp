#ifndef RENDER_H_
#define RENDER_H_

#include <string>
#include "scene.hpp"

void render(Scene& scene, std::vector<std::vector<Color>>& pixels);
Color cast_ray(Scene& scene, Ray& ray);
void write_ppm(std::vector<std::vector<Color>>& pixels, std::string path);

#endif