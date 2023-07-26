#ifndef SCENE_H_
#define SCENE_H_

#include <string>
#include <vector>
#include "geometry.hpp"
#include "graphics.hpp"

struct View {
    // corners of viewing plane
    Vector ul, ur, ll, lr;
};

struct Scene {
    Vector eye_pos, up_dir, view_dir;
    float fov_h;
    float img_w, img_h;
    View view;
    Color bkg_color;
    std::vector<Material> materials;
    std::vector<Sphere> spheres;
    std::vector<PointLight> point_lights;
};

void load_scene(Scene& scene, std::string path);
void define_view(Scene& scene);

#endif