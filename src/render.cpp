#include <iostream>
#include <fstream>
#include "render.hpp"

void render(Scene& scene, std::vector<std::vector<Color>>& pixels) {
    std::cout << "Rendering..." << std::endl;

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
    return scene.bkg_color;
}

void write_ppm(std::vector<std::vector<Color>>& pixels, std::string path) {
    std::cout << "Writing to \"" << path << "\"..." << std::endl;

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