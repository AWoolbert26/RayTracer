#include <iostream>
#include <fstream>
#include "Vec.h"
#include "Color.h"
#include "Ray.h"
#include "Camera.h"

int main() {

    Camera my_cam = Camera();
    my_cam.take_picture();

//    std::ofstream file("output.ppm");
//
//    file << "P3\n" << image_width << " " << image_height << "\n255\n";
//
//    for (int j = 0; j < image_height; ++j) {
//        for (int i = 0; i < image_width; ++i) {
//            auto r = double(i) / (image_width-1);
//            auto g = double(j) / (image_height-1);
//            auto b = 0;
//
//            int ir = static_cast<int>(255.999 * r);
//            int ig = static_cast<int>(255.999 * g);
//            int ib = static_cast<int>(255.999 * b);
//
//            file << ir << ' ' << ig << ' ' << ib << '\n';
//        }
//    }
//
//    file.close();

    std::cout << "Generated " << "output.ppm" << std::endl;
    return 0;

}
