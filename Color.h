//
// Created by Andrew Woolbert on 9/7/23.
//

#include <iostream>
#include <string>
#ifndef OUTPUT_PPM_COLOR_H
#define OUTPUT_PPM_COLOR_H

using namespace std;

class Color {
    public:
    double r, g, b, brightness;

    //  Initializers
    Color();
    Color(double, double, double, double);

    //  Getter functions
    double getR() {
        return r;
    }
    double getG() {
        return g;
    }
    double getB() {
        return b;
    }
    double getBrightness() {
        return brightness;
    }

    void print() {
        std::cout<<r<<" "<<g<<" "<<b<<std::endl;
    }

    string ppmOutput() {
        // scale colors according to selected rgb scale (256) and brightness
        int convertedR = static_cast<int>(255.999 * r * brightness);
        int convertedG = static_cast<int>(255.999 * g * brightness);
        int convertedB = static_cast<int>(255.999 * b * brightness);
        return to_string(convertedR) + ' ' + to_string(convertedG) + ' ' + to_string(convertedB) + '\n';
    }
};

Color:: Color() {
    r = 0;
    g = 0;
    b = 0;
    brightness = .2;
}

Color::Color(double r_val, double g_val, double b_val, double brightness_val) {
    r = r_val;
    g = g_val;
    b = b_val;
    brightness = brightness_val;
}
#endif //OUTPUT_PPM_COLOR_H
