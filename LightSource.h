//
// Created by Andrew Woolbert on 9/13/23.
//

#ifndef OUTPUT_PPM_LIGHTSOURCE_H
#define OUTPUT_PPM_LIGHTSOURCE_H
#include "Vec.h"
#include "Color.h"


class LightSource {
    public:
    Point origin;
    double intensity;

    // Initializer
    LightSource();
    LightSource(const Point&, const double&);
};

LightSource::LightSource() {
    origin = Point(0, 8, -1);
    intensity = 0.5;
}
LightSource::LightSource(const Point &light_origin, const double &light_intensity) {
    origin = light_origin;
    intensity= light_intensity;
}

#endif //OUTPUT_PPM_LIGHTSOURCE_H
