//
// Created by Andrew Woolbert on 9/7/23.
//

#ifndef OUTPUT_PPM_SPHERE_H
#define OUTPUT_PPM_SPHERE_H
#include "Vec.h"
#include "Hitable.h"


class Sphere : public Hitable {
    private:
    Point center;
    double radius;
    Color color;

    public:

//  Initializer
    Sphere();
    Sphere(const Point&, const double&, Color sphere_color);

//  Check if the sphere is hit or not and record the closest hit
    bool hit(Ray& r, double ray_distance_min, double ray_distance_max, HitRecord& hit) const override {
        Vec oc = r.origin - center;

        // This is basic algebra finding the intersection between a ray and a sphere in 3d.
        // Code is from https://raytracing.github.io/books/RayTracingInOneWeekend.html.
        auto a = (r.direction.length()) * (r.direction.length());
        auto half_b = dot(oc, r.direction);
        auto c = (oc.length() * oc.length()) - radius*radius;

        auto discriminant = half_b*half_b - a*c;
        if (discriminant < 0) {
            return false;
        }
        auto sqrtd = sqrt(discriminant);

        auto root = (-half_b - sqrtd) / a;
        if (root <= ray_distance_min || ray_distance_max <= root) {
            root = (-half_b + sqrtd) / a;
            if (root <= ray_distance_min || ray_distance_max <= root)
                return false;
        }

        hit.dist_along_ray = root;
        hit.hit_point = r.pointAlongRay(hit.dist_along_ray);
        Vec hit_normal = (hit.hit_point - center) / radius;
        hit.hit_color = color;
        hit.set_normal(r, hit_normal);

        return true;
    }


};

Sphere::Sphere() {
    center = Point(0, 0, 0);
    radius = 1;
    color = Color(1,1,1,1);
}

Sphere::Sphere(const Point &sphere_center, const double &sphere_radius, Color sphere_color) {
    center = sphere_center;
    radius = sphere_radius;
    color = sphere_color;
}

#endif //OUTPUT_PPM_SPHERE_H
