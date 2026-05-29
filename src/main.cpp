#include <memory>
#include "raytracer_common.h"
#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"

int main() {
    hittable_list world;

    shared_ptr<lambertian> ground_material = make_shared<lambertian>(color(0.5, 0.5, 0.5));
    world.add(make_shared<sphere>(point3(0, -1000, 0), 1000, ground_material));

    // Many small random balls
    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            double choose_mat = random_double();
            point3 center(a + 0.9*random_double(), 0.2, b + 0.9*random_double());

            // Skip positions that would overlap with the 3 main spheres
            if ((center - point3(-4, 0.2, 0)).length() < 1.0) continue;
            if ((center - point3( 4, 0.2, 0)).length() < 1.0) continue;
            if ((center - point3( 0, 0.2,-5)).length() < 1.0) continue;

            shared_ptr<material> mat;
            if (choose_mat < 0.8) {
                auto albedo = color::random() * color::random();
                mat = make_shared<lambertian>(albedo);
            } else if (choose_mat < 0.95) {
                auto albedo = color::random(0.5, 1);
                auto fuzz = random_double(0, 0.5);
                mat = make_shared<metal>(albedo, fuzz);
            } else {
                mat = make_shared<dielectric>(1.5);
            }
            world.add(make_shared<sphere>(center, 0.2, mat));
        }
    }

    // 3 main spheres (pushed around so they frame the letters)
    world.add(make_shared<sphere>(point3( 0, 1, -5), 1.0, make_shared<dielectric>(1.5)));
    world.add(make_shared<sphere>(point3(-4, 1,  0), 1.0, make_shared<lambertian>(color(0.4, 0.2, 0.1))));
    world.add(make_shared<sphere>(point3( 4, 1,  0), 1.0, make_shared<metal>(color(0.7, 0.6, 0.5), 0.0)));

    // ── "JOE" spelled in glass spheres ──────────────────────────────────────
    // Grid: 3 columns × 7 rows per letter, radius r, spacing s between centres.
    // One blank column separates consecutive letters.
    // Letters are centred at x=0, sit on the ground (y_bottom = r), at z=0.
    //
    // Column x positions:
    //   J: -1.50  -1.20  -0.90
    //   O: -0.30   0.00   0.30
    //   E:  0.90   1.20   1.50
    //
    // Row y positions (row 0 = bottom):
    //   y = r + row * s
    // ────────────────────────────────────────────────────────────────────────
    auto glass = make_shared<dielectric>(1.5);
    const double r = 0.12;
    const double s = 0.30;

    // Bitmaps: [row][col], row 0 = bottom, row 6 = top
    int J[7][3] = {
        {0, 1, 0},   // row 0: bottom of hook
        {1, 0, 1},   // row 1: hook sides
        {0, 0, 1},   // row 2
        {0, 0, 1},   // row 3
        {0, 0, 1},   // row 4
        {0, 0, 1},   // row 5
        {1, 1, 1},   // row 6: top bar
    };
    int O[7][3] = {
        {0, 1, 0},   // row 0
        {1, 0, 1},   // row 1
        {1, 0, 1},   // row 2
        {1, 0, 1},   // row 3
        {1, 0, 1},   // row 4
        {1, 0, 1},   // row 5
        {0, 1, 0},   // row 6
    };
    int E[7][3] = {
        {1, 1, 1},   // row 0: bottom bar
        {1, 0, 0},   // row 1
        {1, 0, 0},   // row 2
        {1, 1, 0},   // row 3: middle bar (shorter, classic E)
        {1, 0, 0},   // row 4
        {1, 0, 0},   // row 5
        {1, 1, 1},   // row 6: top bar
    };

    const double j_x0 = -1.50;
    const double o_x0 = -0.30;
    const double e_x0 =  0.90;

    for (int row = 0; row < 7; row++) {
        double y = r + row * s;
        for (int col = 0; col < 3; col++) {
            double dx = col * s;
            if (J[row][col])
                world.add(make_shared<sphere>(point3(j_x0 + dx, y, 0), r, glass));
            if (O[row][col])
                world.add(make_shared<sphere>(point3(o_x0 + dx, y, 0), r, glass));
            if (E[row][col])
                world.add(make_shared<sphere>(point3(e_x0 + dx, y, 0), r, glass));
        }
    }

    camera cam;
    
    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 1200;
    cam.samples_per_pixel = 500;
    cam.max_depth = 50;

    cam.vfov = 25;
    cam.lookfrom = point3(0, 2, 10);
    cam.lookat = point3(0, 1, 0);
    cam.vup = point3(0, 1, 0);
    cam.defocus_angle = 0.6;
    cam.focus_distance = 10.0;

    cam.render(world);
}
