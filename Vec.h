//
// Created by Andrew Woolbert on 9/1/23.
//

#ifndef RAYTRACER_VEC_H
#define RAYTRACER_VEC_H
#include <cmath>
#include <iostream>

class Vec {
    public:
    double x, y, z;

    //  Initializers
    Vec();
    Vec(double, double, double);

    //  Basic get functions
    double getX() {return x;}
    double getY() {return y;}
    double getZ() {return z;}

    //  Basic vector operations
    Vec operator+(Vec u) {
        return Vec(x + u.getX(), y + u.getY(), z + u.getZ());
    }
    Vec operator-(Vec u) {
        return Vec(x - u.getX(), y - u.getY(), z - u.getZ());
    }
    Vec operator*(double t) {
        return Vec(x * t, y * t, z * t);
    }
    Vec operator/(double t) {
        return *this * (1 / t);
    }

    //  Additional vector operations
    Vec negate() {
        return Vec(-x, -y, -z);
    }
    double length() {
        return sqrt(x * x + y * y + z * z);
    }
    void print() {
        std::cout << x << ' ' << y << ' ' << z << std::endl;
    }
    Vec normalize() {
        return *this / this->length();
    }

};

// Dot and Cross are external functions for increased flexibility
double dot(Vec u, Vec v) {
    return u.getX() * v.getX() + u.getY() * v.getY() + u.getZ() * v.getZ();
}
Vec cross(Vec u, Vec v) {
    return Vec(
            u.getY() * v.getZ() - u.getZ() * v.getY(),
            u.getZ() * v.getX() - u.getX() * v.getZ(),
            u.getX() * v.getY() - u.getY() * v.getX());
}

// Using point to avoid confusion
using Point = Vec;

Vec:: Vec() {
    x = 0;
    y = 0;
    z = 0;
}

Vec::Vec(double xVal, double yVal, double zVal) {
    x = xVal;
    y = yVal;
    z = zVal;
}

#endif //RAYTRACER_VEC_H
