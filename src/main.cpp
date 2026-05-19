#include <memory>
#include "raytracer_common.h"
#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"

int main() {
    // WORLD
    hittable_list world;


    // OBJECTS
    // v2: zoomed out view
    shared_ptr<lambertian> material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
    shared_ptr<lambertian> material_center = make_shared<lambertian>(color(0.1, 0.2, 0.5));
    shared_ptr<metal> material_right = make_shared<metal>(color(0.8, 0.6, 0.2), 1.0); // very fuzzy
    shared_ptr<dielectric> material_left = make_shared<dielectric>(1.50);
    shared_ptr<dielectric> material_bubble = make_shared<dielectric>(1.0 / 1.50);
    
    world.add(make_shared<sphere>(point3{0.0,-100.5,-1.0}, 100.0, material_ground));
    world.add(make_shared<sphere>(point3{0.0, 0.0, -1.2}, 0.5, material_center));
    world.add(make_shared<sphere>(point3{-1.0, 0.0, -1.0}, 0.4, material_bubble));
    world.add(make_shared<sphere>(point3{-1.0, 0.0, -1.0}, 0.5, material_left));
    world.add(make_shared<sphere>(point3{1.0, 0.0, -1.0}, 0.5, material_right));

    // V1: Wide angle camera
    // double R = std::cos(pi / 4);

    // shared_ptr<lambertian> material_left = make_shared<lambertian>(color(0.0, 0.0, 1.0));
    // shared_ptr<lambertian> material_right = make_shared<lambertian>(color(1.0, 0.0, 0.0));

    // world.add(make_shared<sphere>(point3{-R, 0.0, -1.0}, R, material_left));
    // world.add(make_shared<sphere>(point3{R, 0.0, -1.0}, R, material_right));
    
    // CAMERA
    camera cam;

    // initialize user values
    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 400;
    cam.samples_per_pixel = 100;
    cam.max_depth = 50;

    // distant view
    // cam.vfov = 90;
    cam.lookfrom = point3(-2.0, 2.0, 1.0);
    cam.lookat = point3(0.0, 0.0, -1.0);
    cam.vup = point3(0.0, 1.0, 0.0);

    // zoom in
    cam.vfov = 20;
    
    // render()
    cam.render(world);
}