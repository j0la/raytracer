#include <iostream>
#include "scene.hpp"

using namespace std;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cout << "ERROR: expected \"./render [FILENAME].txt\"" << endl;
        exit(1);
    }

    string ipath = argv[1];
    string opath = ipath.substr(0, ipath.find_last_of('.')) + ".ppm";

    Scene scene;
    load_scene(scene, ipath);
    define_view(scene);
}