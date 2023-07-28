#include <iostream>
#include <fstream>
#include <cmath>
#include "render.hpp"

void render(Scene& scene, std::vector<std::vector<Color>>& pixels) {
    size_t cols = pixels.size();
    size_t rows = pixels.front().size();

    // calculate step size between pixel centers
    // pixel (i, j) center at   ul + (i * step_h) + (j * step_v)
    Vector step_h = (scene.view.ur - scene.view.ul) / (float)(cols - 1);
    Vector step_v = (scene.view.ll - scene.view.ul) / (float)(rows - 1);

    for (size_t j = 0; j < rows; j++) {
        for (size_t i = 0; i < cols; i++) {
            Vector pixel_center = scene.view.ul + (step_h * i) + (step_v * j);
            Ray ray = {
                .origin = scene.eye_pos,
                .dir = v_norm(pixel_center - scene.eye_pos)
            };
            pixels[i][j] = cast_ray(scene, ray);
        }
    }
}

Color cast_ray(Scene& scene, Ray& ray) {
    // intersection displacement along ray
    float t = -1;
    // intersected sphere index
    size_t s = -1;

    for (size_t i = 0; i < scene.spheres.size(); i++) {
        Sphere& sphere = scene.spheres[i];
        float x = intersect(ray, sphere);
        if (x > 0 && (t < 0 || x < t)) {
            // either the first intersection or the nearest
            t = x;
            s = i;
        }
    }

    // no intersection
    if (t <= 0) return scene.bkg_color;

    // intersection found
    Vector ipt = ray.origin + ray.dir * t;
    Sphere& sphere = scene.spheres.at(s);
    Material& material = scene.materials.at(sphere.m);

    // surface normal at intersection
    Vector N = v_norm((ipt - sphere.origin) / sphere.radius);

    // direction to eye / ray origin
    Vector V = v_norm(ray.dir * -1);

    Color energy = material.od * material.ka;

    for (PointLight& light : scene.point_lights) {
        // distance & direction to light
        Vector L = v_norm(light.origin - ipt);
        float light_d = v_length(light.origin - ipt);

        // halfway between ray & light
        Vector H = v_norm(L + V);

        Color diffuse = material.od * material.kd * std::max(N * L, 0.0f);
        Color specular = material.os * material.ks * std::pow(std::max(N * H, 0.0f), material.n);
        energy = energy + light.color * (diffuse + specular);
        energy = clamp(energy, 0, 1);
    }

    return energy;
}

void write_ppm(std::vector<std::vector<Color>>& pixels, std::string path) {
    std::ofstream fs;
    fs.open(path);
    if (!fs.is_open()) {
        std::cout << "ERROR: failed to open \"" + path + "\"" << std::endl;
        exit(1);
    }

    fs << "P3 " << pixels.size() << " " << pixels.front().size() << " 255" << std::endl;

    for (std::vector<Color>& col : pixels) {
        for (Color& pixel : col) {
            fs << std::to_string((uint8_t)(pixel.r * 255)) << " "
                << std::to_string((uint8_t)(pixel.g * 255)) << " "
                << std::to_string((uint8_t)(pixel.b * 255)) << std::endl;
        }
    }

    fs.close();
}