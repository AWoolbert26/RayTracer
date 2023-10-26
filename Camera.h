//
// Created by Andrew Woolbert on 9/7/23.
//

#ifndef OUTPUT_PPM_CAMERA_H
#define OUTPUT_PPM_CAMERA_H
#include "Vec.h"
#include "Ray.h"
#include "Sphere.h"
#include "HitableList.h"
#include "LightSource.h"
#include <iostream>
#include <fstream>
#include <string>
#include <random>

const double infinity = std::numeric_limits<double>::infinity();

class Camera {
    public:
    //  Output image size determined through aspect ratio and image width
    double aspect_ratio = 16 / 9.0;
    int image_width = 2000;
    HitableList world;
    LightSource light;

    void take_picture() {
        initialize_camera();
        initialize_world();

        std::ofstream file("output.ppm");

        //Initialize random number generator
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(-0.5, 0.5);

        // Render
        file << "P3\n" << image_width << " " << image_height << "\n255\n";

        for (int j = 0; j < image_height; ++j) {
            for (int i = 0; i < image_width; ++i) {
                Color final_color = Color();
                int num_rays = 4;
                for (int k = 0; k < num_rays; ++k) {
                    Point current_pixel_center = upper_left_pixel_loc + (pixel_vertical_delta * (j + dis(gen))) + (pixel_horizontal_delta * (i + dis(gen)));
                    Vec direction_to_pixel = current_pixel_center - camera_origin;
                    Ray ray = Ray(camera_origin, direction_to_pixel);

                    Color pixel_color = find_color_for_ray(ray, world, light);
                    final_color += pixel_color / num_rays;
                }
//                Point current_pixel_center = upper_left_pixel_loc + (pixel_vertical_delta * j) + (pixel_horizontal_delta * i);
//                Vec direction_to_pixel = current_pixel_center - camera_origin;
//                Ray ray = Ray(camera_origin, direction_to_pixel);
//
//                Color pixel_color = find_color_for_ray(ray, world, light);
                file << final_color.ppmOutput();
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
        camera_origin = Point(0, 0, 2);

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
        upper_left_pixel_loc = viewport_upper_left + ((pixel_horizontal_delta + pixel_vertical_delta) * 0.8);

    }

    void initialize_world() {
        world.add(make_shared<Sphere>(Point(0,0,-1), 0.5, Color(1,0,0,0.2)));
        world.add(make_shared<Sphere>(Point(1.5,0.5,-1), 1, Color(0,1,0,0.2)));
        world.add(make_shared<Sphere>(Point(0,-1000.5,-1), 1000, Color(0.4,0.4,0.4,0.2)));
        light = LightSource(Point(10, 10, -1), 2);
    }

    Color find_color_for_ray(Ray& ray, const HitableList& objects, LightSource light_source) {
        HitRecord hit;
        if (objects.hit(ray, 0, infinity, hit)) {
            Color hit_color = hit.hit_color;
            Point hit_point = hit.hit_point;
            Vec vec_to_light = light.origin - hit_point;
            Vec normal_vec_to_light = vec_to_light / vec_to_light.length();
            Ray normal_ray_to_light = Ray(hit_point, normal_vec_to_light);
            Vec hit_normal = hit.hit_normal;
            HitRecord new_hit;
            if (objects.hit(normal_ray_to_light, 0.001, vec_to_light.length(), new_hit)) {
                return hit_color;
            } else {
                double angle = acos(dot(hit_normal, vec_to_light)/(hit_normal.length() * vec_to_light.length())) * 57.2958;
                double angle_scaled = angle / 90;
                hit_color.brightness += abs(1 - angle_scaled) * light_source.intensity;
                return hit_color;
            }

        } else {
            return Color(0.1,0.1,0.1,1);
        }
    }
};

#endif //OUTPUT_PPM_CAMERA_H
