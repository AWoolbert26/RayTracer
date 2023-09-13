//
// Created by Andrew Woolbert on 9/7/23.
//

#ifndef OUTPUT_PPM_CAMERA_H
#define OUTPUT_PPM_CAMERA_H
#include "Vec.h"
#include "Ray.h"
#include "Sphere.h"
#include "HitableList.h"
#include <iostream>
#include <fstream>
#include <string>

const double infinity = std::numeric_limits<double>::infinity();

class Camera {
    public:
    //  Output image size determined through aspect ratio and image width
    double aspect_ratio = 16 / 9.0;
    int image_width = 1000;
    HitableList world;

    void take_picture() {
        initialize_camera();
        initialize_world();

        std::ofstream file("output.ppm");

        // Render

        file << "P3\n" << image_width << " " << image_height << "\n255\n";

        for (int j = 0; j < image_height; ++j) {
            for (int i = 0; i < image_width; ++i) {
                Point current_pixel_center = upper_left_pixel_loc + (pixel_vertical_delta * j) + (pixel_horizontal_delta * i);
                Vec direction_to_pixel = current_pixel_center - camera_origin;
                Ray ray = Ray(camera_origin, direction_to_pixel);

                Color pixel_color = find_color_for_ray(ray, world);
                pixel_color.ppmOutput();
                file << pixel_color.ppmOutput();
            }
        }
        file.close();
    }

    private:
    int image_height;
    Point camera_origin;
    Point upper_left_pixel_loc;
    Vec pixel_horizontal_delta;
    Vec pixel_vertical_delta;

    void initialize_camera() {
        image_height = static_cast<int>(image_width / aspect_ratio);
        camera_origin = Point(0, 0, 0);

        // Initial viewport variables, determine what size it should be
        auto distance_from_cam = 1.0;
        auto viewport_width = 32/9;
        auto viewport_height = viewport_width / aspect_ratio;

        // Creation of the viewport borders
        Vec horizontal_viewport_border = Vec(viewport_width, 0, 0);
        Vec vertical_viewport_border = Vec(0, -viewport_height, 0);

        // We need to find where each pixel corresponds to on the viewport. We can do this by finding the top left
        // pixel and finding the vectors to move between each pixel.
        pixel_horizontal_delta = horizontal_viewport_border / image_width;
        pixel_vertical_delta = vertical_viewport_border / image_height;
        Point viewport_upper_left = camera_origin - Vec(0, 0, distance_from_cam) - horizontal_viewport_border / 2 - vertical_viewport_border / 2;
        upper_left_pixel_loc = viewport_upper_left + ((pixel_horizontal_delta + pixel_vertical_delta) * 0.5);

    }

    void initialize_world() {
        world.add(make_shared<Sphere>(Point(0,0,-1), 0.5, Color(1,0,0,1)));
        world.add(make_shared<Sphere>(Point(0,-100.5,-1), 100, Color(0,1,0,1)));
    }


    Color find_color_for_ray(Ray& ray, const HitableList& objects) {
        HitRecord hit;
        if (objects.hit(ray, 0, infinity, hit)) {
            hit.hit_normal.print();
            return Color(abs(hit.hit_normal.getX()), abs(hit.hit_normal.getY()), abs(hit.hit_normal.getZ()), 1);
        } else {
            return Color(0.5,0.5,0.5,1);
        }

    }
};

#endif //OUTPUT_PPM_CAMERA_H
