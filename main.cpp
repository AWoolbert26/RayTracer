#include <iostream>
#include <fstream>
#include "Vec.h"
#include "Color.h"
#include "Ray.h"
#include "Camera.h"

int main() {

    Camera my_cam = Camera();
    my_cam.take_picture();

    std::cout << "Generated " << "output.ppm" << std::endl;
    return 0;

}
