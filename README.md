# Ray Tracer (in a weekend)

## Purpose

The purpose of this project was to get familiar with introductory cpp concepts & syntax.

Prior to this, my strongest and most familiar language was python *interpreted + dynamic + strong*
whereas cpp is *compiled + static + strong/weak* (mostly strong but contains some weak attributes)

Main learnings include:
- internalizing how the compiler works (internal/ external linkage + Translation units)
- variables, pointers & references
- OOP in cpp (virtual methods, destructor, overloading + overriding)
- ray tracing shenanigans

## Quick setup

**Prerequisites**
- C++20 compiler (clang or gcc)
- CMake ≥ 3.20
- Ninja — `brew install ninja`
- vcpkg — clone it and export `VCPKG_ROOT` pointing to that directory

```bash
# 1. export vcpkg root (add this to your shell profile to make it permanent)
export VCPKG_ROOT=~/vcpkg

# 2. configure — creates ./build using the Ninja generator + vcpkg toolchain
cmake --preset vcpkg

# 3. compile
cmake --build build

# 4. render (outputs a PPM image)
./build/RayTracer > image.ppm
```

* Note: at the default settings (`image_width = 1200`, `samples_per_pixel = 500`) the render takes several minutes. Lower those values in `src/main.cpp` for a quick preview.

## Project structure

```
cpp_ray_tracer/
├── src/
│   ├── raytracer_common.h   shared includes, constants (pi, infinity), random_double()
│   ├── vec3.h               vec3 / point3 type, math ops, refract(), random helpers
│   ├── color.h              color alias, write_color(), gamma correction
│   ├── ray.h                ray struct (origin + direction)
│   ├── interval.h           interval struct (min/max, surrounds, clamp)
│   ├── hittable.h           hittable abstract base class + hit_record
│   ├── hittable_list.h      scene container (list of hittables)
│   ├── sphere.h             sphere : hittable
│   ├── material.h           material base class + lambertian, metal, dielectric
│   ├── camera.h             camera setup, render loop, ray_color()
│   └── main.cpp             entry point — scene setup for each chapter
├── renders/                 selected renders saved from key stages of the project
├── CMakeLists.txt           build target definition
└── CMakePresets.json        configure preset (Ninja generator + vcpkg toolchain)
```

## Missing concepts in this text book

1. multi-threading & concurrency 
2. STL containers 
3. templates & generic programming 
4. smart pointers

how my next project (market data ingestor) will help me learn these concepts:

1. multi-threading & concurrency => create core engine
2. STL containers => used to manage order book
3. templates & generic programming => handling diverse asset types
4. smart pointers => managing streaming message pipelines

## Places AI was used

- assist in this README (specically the `quick set up` & `project structure` sections)
- write code to generate `JOE` as the final image
    - was too lazy to figure out geometrically how i should be placing the balls
