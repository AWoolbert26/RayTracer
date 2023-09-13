//
// Created by Andrew Woolbert on 9/9/23.
//

#ifndef OUTPUT_PPM_HITABLELIST_H
#define OUTPUT_PPM_HITABLELIST_H

#include "Hitable.h"
#include "Ray.h"

#include <memory>
#include <vector>

using std::shared_ptr;
using std::make_shared;

class HitableList {
public:
    std::vector<shared_ptr<Hitable>> objects;

    HitableList() {}
    HitableList(shared_ptr<Hitable> object) { add(object); }

    void clear() { objects.clear(); }

    void add(shared_ptr<Hitable> object) {
        objects.push_back(object);
    }

    bool hit(Ray& r, double ray_distance_min, double ray_distance_max, HitRecord& hit) const {
        HitRecord temp_rec;
        bool hit_anything = false;
        auto closest_so_far = ray_distance_max;

        for (const auto& object : objects) {
            if (object->hit(r, ray_distance_min, closest_so_far, temp_rec)) {
                hit_anything = true;
                closest_so_far = temp_rec.dist_along_ray;
                hit = temp_rec;
            }
        }

        return hit_anything;
    }
};


#endif //OUTPUT_PPM_HITABLELIST_H
