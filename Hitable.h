//
// Created by Andrew Woolbert on 9/8/23.
//

#ifndef OUTPUT_PPM_HITABLE_H
#define OUTPUT_PPM_HITABLE_H
#include "Color.h"
#include "Ray.h"
#include <vector>
#include <cmath>

class HitRecord {
    public:
    double dist_along_ray;
    Point hit_point;
    Vec hit_normal;
    Color hit_color;
    bool outside_face;

    void set_normal(const Ray& r, Vec& normal) {
        outside_face = dot(r.direction, normal) < 0;
        hit_normal = outside_face ? normal : normal * -1;
    }
};

class Hitable {
    public:
    virtual ~Hitable() = default;

    virtual bool hit(Ray& r, double ray_tmin, double ray_tmax, HitRecord& rec) const = 0;
};


#endif //OUTPUT_PPM_HITABLE_H
