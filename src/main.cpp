#include "raytracer_common.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"

color ray_color(const ray& ray, const hittable& world) {
    // hit
    hit_record record;
    if (world.hit(ray, interval(0, infinity), record)) {
        return 0.5 * (record.normal + color{1,1,1});
    }

    // didnt hit
    vec3 unit_direction = unit_vector(ray.direction());
    double a = 0.5 * (unit_direction.y() + 1);
    color white_color{1, 1, 1};
    color blue_color(0.5, 0.7, 1.0);
    return (1 - a) * white_color + a * blue_color;
}

int main() {
    auto aspect_ratio = 16.0 / 9.0;
    int image_width = 400;

    // image height
    int image_height = int(image_width / aspect_ratio);
    // image_height if image_height > 1 else 1
    image_height = image_height > 1 ? image_height : 1;

    // WORLD
    hittable_list world;
    world.add(make_shared<sphere>(point3{0, 0, -1}, 0.5));
    world.add(make_shared<sphere>(point3{0,-100.5,-1}, 100));

    // CAMERA
    auto focal_length = 1.0;
    point3 camera_center{0,0,0};
    // viewport
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * (double(image_width) / image_height);

    // viewport vectors
    vec3 viewport_u{viewport_width, 0, 0};
    vec3 viewport_v{0, -viewport_height, 0};

    // viewport delta vectors
    vec3 pixel_delta_u = viewport_u / image_width;
    vec3 pixel_delta_v = viewport_v / image_height;

    // calc location of upper left px
    auto viewport_upper_left = camera_center - viewport_u / 2 - viewport_v / 2 - vec3{0, 0, focal_length};
    auto pixel_upper_left_loc = viewport_upper_left + 0.5 * pixel_delta_u + 0.5 * pixel_delta_u;

    // RENDER IMG
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    for (int i = 0; i < image_height; i++) {
        // progress indicator: start + intermediate
        std::clog << "\rScanlines remaining:" << (image_height - i) << " / " << image_height << ' ' << std::flush;
        for (int j = 0; j < image_width; j++) {
            // next pixel center (we are rendering px by px)
            point3 pixel_center = pixel_upper_left_loc + i * pixel_delta_v + j * pixel_delta_u;

            // ray direction
            vec3 ray_direction = pixel_center - camera_center;

            // create ray
            ray ray{camera_center, ray_direction};
            // ray's color
            color pixel_color = ray_color(ray, world);
            // create image
            write_color(std::cout, pixel_color);
        }
    }
    // progress indicator: end
    std::clog << "\rdone.                      \n";
}