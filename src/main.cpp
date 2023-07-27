#include <iostream>
#include "scene.hpp"
#include "graphics.hpp"
#include "render.hpp"

using namespace std;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cout << "ERROR: expected \"./render [FILENAME].txt\"" << endl;
        exit(1);
    }

    string ipath = argv[1];
    string opath = ipath.substr(0, ipath.find_last_of('.')) + ".ppm";

    std::cout << "Loading \"" << ipath << "\"..." << std::endl;
    Scene scene;
    load_scene(scene, ipath);
    define_view(scene);

    std::vector<std::vector<Color>> pixels(scene.img_w, std::vector<Color>(scene.img_h));

    std::cout << "Rendering..." << std::endl;
    render(scene, pixels);

    std::cout << "Writing to \"" << opath << "\"..." << std::endl;
    write_ppm(pixels, opath);
}