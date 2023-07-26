#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include "scene.hpp"

using namespace std;

void load_scene(Scene& scene, std::string path) {
    cout << "Loading \"" << path << "\"..." << endl;

    std::ifstream fs;
    fs.open(path);
    if (!fs.is_open()) {
        cout << "ERROR: failed to open \"" + path + "\"" << endl;
        exit(1);
    }

    std:string line;
    while (getline(fs, line)) {
        // parse lines of scene description file
        // expects one keyword per line followed by parameters separated by whitespace
        std::stringstream ss(line);
        std::string token;
        ss >> token;

        // parse recognized keywords
        if (token == "eye") {
            // eye x y z
            ss >> scene.eye_pos.x >> scene.eye_pos.y >> scene.eye_pos.z;
        } else if (token == "viewdir") {
            // viewdir x y z
            // eye view direction
            ss >> scene.view_dir.x >> scene.view_dir.y >> scene.view_dir.z;
        } else if (token == "updir") {
            // updir x y z
            // eye up direction
            ss >> scene.up_dir.x >> scene.up_dir.y >> scene.up_dir.z;
        } else if (token == "hfov") {
            // hfov deg
            // horizontal field of view
            ss >> scene.fov_h;
        } else if (token == "imsize") {
            // imsize width height
            // image resolution (pixels)
            ss >> scene.img_w >> scene.img_h;
        } else if (token == "bkgcolor") {
            // bkgcolor r g b
            // background color components [0, 1]
            ss >> scene.bkg_color.r >> scene.bkg_color.g >> scene.bkg_color.b;
        } else if (token == "material") {
            // material Odr Odg Odb Osr Osg Osb ka kd ks n α η
            // applies to all following objects until a new material is defined
            // Odr Odg Odb Osr Osg Osb: diffuse and specular object color [0, 1]
            // ka kd ks: ambient, diffuse, and specular reflectivity [0, 1]
            // n: specular falloff (higher = focused highlight)
            // α: opacity [0, 1]
            // η: refractive index
            Material m;
            ss >> m.od.r >> m.od.g >> m.od.b >> m.os.r >> m.os.g >> m.os.b >> m.ka >> m.kd >> m.ks >> m.n >> m.a >> m.i;
            scene.materials.push_back(m);
        } else if (token == "sphere") {
            // sphere x y z r
            Sphere s { .material = scene.materials.back() };
            ss >> s.origin.x >> s.origin.y >> s.origin.z >> s.radius;
            scene.spheres.push_back(s);
        } else if (token == "pointlight") {
            // pointlight x y z r g b
            PointLight l;
            ss >> l.origin.x >> l.origin.y >> l.origin.z >> l.color.r >> l.color.g >> l.color.b;
            scene.point_lights.push_back(l);
        }
    }

    fs.close();
}

void define_view(Scene& scene) {
    // unit view direction
    Vector n = v_norm(scene.view_dir);
    // axes
    Vector u = v_norm(v_cross(scene.view_dir, scene.up_dir)); // horizontal
    Vector v = v_norm(v_cross(u, scene.view_dir)); // vertical
    Vector w = n * -1;
    // dimensions
    float aspect_ratio = (float)scene.img_w / (float)scene.img_h;
    float view_d = 10; // arbitrary distance from eye, dimensions scale proportionally regardless of value
    float view_w = 2 * view_d * tan(0.5 * scene.fov_h * (pi / 180));
    float view_h = view_w / aspect_ratio;
    // corners
    scene.view.ul = scene.eye_pos + n * view_d - u * (view_w  / 2) + v * (view_h / 2);
    scene.view.ur = scene.eye_pos + n * view_d + u * (view_w  / 2) + v * (view_h / 2);
    scene.view.ll = scene.eye_pos + n * view_d - u * (view_w  / 2) - v * (view_h / 2);
    scene.view.lr = scene.eye_pos + n * view_d + u * (view_w  / 2) - v * (view_h / 2);
}