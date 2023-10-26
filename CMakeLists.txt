cmake_minimum_required(VERSION 3.26)
project(RayTracer)

set(CMAKE_CXX_STANDARD 17)

add_executable(RayTracer main.cpp
        Vec.h
        Color.h
        Ray.h
        Sphere.h
        Camera.h
        Hitable.h
        HitableList.h
        LightSource.h
)
