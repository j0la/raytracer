#include <iostream>
#include <fstream>
#include "render.hpp"

void render(Scene& scene, std::vector<std::vector<Color>>& pixels) {
    std::cout << "Rendering..." << std::endl;
    
    for (std::vector<Color>& col : pixels) {
        for (Color& pixel : col) {
            pixel = scene.bkg_color;
        }
    }
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