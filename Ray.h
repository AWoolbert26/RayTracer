//
// Created by Andrew Woolbert on 9/7/23.
//

#ifndef OUTPUT_PPM_RAY_H
#define OUTPUT_PPM_RAY_H
#include "Vec.h"


class Ray {
    public:
    Point origin;
    Vec direction;

    //  Initializers
    Ray();
    Ray(Point &origin, Vec &direction);

    //  Determines a point along a ray given the ray's origin, direction, and distance in that direction
    Point pointAlongRay(double t) {
        return origin + (direction * t);
    }

};

Ray::Ray() {
    origin = Point(0, 0, 0);
    direction = Vec(0, 0, 0);
}

Ray::Ray(Point &origin_point, Vec &direction_vec) {
    origin = origin_point;
    direction = direction_vec;
}


#endif //OUTPUT_PPM_RAY_H
