//
// Created by Andrew Woolbert on 9/7/23.
//

#include <iostream>
#include <string>
#ifndef OUTPUT_PPM_COLOR_H
#define OUTPUT_PPM_COLOR_H

using namespace std;

// This class defines the color of a certain object.
// We have 4 member variables, (r,g,b) which correspond to red green and blue, and the brightness of the color
// which we will use to visualize brightness

class Color {
    public:
    double r, g, b, brightness;

    //  Initializers
    Color();
    Color(double, double, double, double);

    // Print method for debugging
    void print() {
        std::cout<<r<<" "<<g<<" "<<b<<" "<<brightness<<::endl;
    }

    Color operator / (double t) {
        return Color(r / t, g / t, b / t, brightness / t);
    }

    void operator += (Color c){
        this->r += c.r;
        this->g += c.g;
        this->b += c.b;
        this->brightness += c.brightness;
    }

    // When adding the color for a given ray to the ppm file we need to convert it to a ppm format
    string ppmOutput() {
        // scale colors according to selected rgb scale (256) and brightness
        r *= brightness;
        g *= brightness;
        b *= brightness;
        correct();
        int convertedR = static_cast<int>(255.999 * r);
        int convertedG = static_cast<int>(255.999 * g);
        int convertedB = static_cast<int>(255.999 * b);
        return to_string(convertedR) + ' ' + to_string(convertedG) + ' ' + to_string(convertedB) + '\n';
    }

    // 
    void correct(){
        double all_light = r + g + b;
        double extralight = all_light - 3;
        if (extralight > 0) {
            r = r + extralight * (r / all_light);
            g = g + extralight * (g / all_light);
            b = b + extralight * (b / all_light);
        }
        if (r > 1) {
            r = 1;
        }
        if (g > 1) {
            g = 1;
        }
        if (b > 1) {
            b = 1;
        }
        if (r < 0) {
            r = 0;
        }
        if (g < 0) {
            g = 0;
        }
        if (b < 0) {
            b = 0;
        }
    }
};

Color:: Color() {
    r = 0;
    g = 0;
    b = 0;
    brightness = 0;
}

Color::Color(double r_val, double g_val, double b_val, double brightness_val) {
    r = r_val;
    g = g_val;
    b = b_val;
    brightness = brightness_val;
}
#endif //OUTPUT_PPM_COLOR_H
