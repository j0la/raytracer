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
            pixels[i][j] = cast_ray(scene, ray, 1, 1);
        }
    }
}

Color cast_ray(Scene& scene, Ray& ray, float ni, int depth) {
    // intersection displacement along ray
    float t = -1;
    // intersected sphere index
    size_t s = -1;

    for (size_t i = 0; i < scene.spheres.size(); i++) {
        Sphere& sphere = scene.spheres[i];
        float x = intersect(ray, sphere);
        if (x > MIN_IXN_DISTANCE && (t < 0 || x < t)) {
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

    // direction to eye / ray origin
    Vector V = v_norm(ray.dir * -1);

    // surface normal at intersection
    Vector N = v_norm(ipt - sphere.origin);
    if (N * V < 0) N = N * -1; // use normal direction closer to incoming ray

    Color energy = material.od * material.ka;

    for (PointLight& light : scene.point_lights) {
        // distance & direction to light
        Vector L = v_norm(light.origin - ipt);
        float light_d = v_length(light.origin - ipt);

        // halfway between ray & light
        Vector H = v_norm(L + V);

        // spawn shadow ray
        float shadow = 1;
        Ray shadow_ray = { .origin = ipt, .dir = L };
        for (Sphere& sphere : scene.spheres) {
            float t = intersect(shadow_ray, sphere);
            // check for intersection between surface & light
            if (t > MIN_IXN_DISTANCE && t < light_d) {
                shadow = shadow * (1 - scene.materials.at(sphere.m).a);
            }
        }

        Color diffuse = material.od * material.kd * std::max(N * L, 0.0f);
        Color specular = material.os * material.ks * std::pow(std::max(N * H, 0.0f), material.f);
        energy = energy + light.color * shadow * (diffuse + specular);
        energy = clamp(energy, 0, 1);
    }

    if (depth >= MAX_RAY_DEPTH) return energy;

    float cos_i = V * N;

    // material fresnel reflectance
    float f0 = std::pow((material.n - ni) / (material.n + ni), 2);
    float fr = f0 + (1 - f0) * std::pow(1 - cos_i, 5);

    // cast reflection ray
    if (material.ks > 0) {
        Ray R = {
            .origin = ipt,
            .dir = v_norm(N * 2 * cos_i - V)
        };
        energy = energy + cast_ray(scene, R, ni, depth + 1) * fr;
        energy = clamp(energy, 0, 1);
    }

    // cast transmission ray
    if (material.a < 1) {
        float n_ratio = ni / material.n;
        float cos_t = 1 - std::pow(n_ratio, 2) * (1 - std::pow(cos_i, 2));
        // total internal reflection when sqrt(cos_t) is undefined (cos_t < 0)
        if (cos_t >= 0) {
            cos_t = std::sqrt(cos_t);

            Ray T = {
                .origin = ipt,
                .dir = v_norm((N * -1) * cos_t + (N * cos_i - V) * n_ratio)
            };
            T.origin = T.origin + T.dir;

            energy = energy + cast_ray(scene, T, material.n, depth + 1) * (1 - fr) * (1 - material.a);
            energy = clamp(energy, 0, 1);
        }
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

    size_t cols = pixels.size();
    size_t rows = pixels.front().size();

    for (size_t j = 0; j < rows; j++) {
        for (size_t i = 0; i < cols; i++) {
            Color pixel = pixels[i][j];
            fs << std::to_string((uint8_t)(pixel.r * 255)) << " "
                << std::to_string((uint8_t)(pixel.g * 255)) << " "
                << std::to_string((uint8_t)(pixel.b * 255)) << std::endl;
        }
    }

    fs.close();
}