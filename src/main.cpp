#include "raytracer_common.h"
// #include "color.h" // provides color
// #include "ray.h"
// #include "vec3.h"

#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"


// double get_t(const point3& center, double radius, const ray& ray) {
//     vec3 oc = center - ray.origin();
//     double a = dot(ray.direction(), ray.direction());
//     double b = -2.0 * dot(ray.direction(), oc);
//     double c = dot(oc, oc) - radius * radius;
//     double discriminant = b * b - 4 * a * c;

//     // >= 0: real soln exists => return smallest t value (nearest point) & assume all points are always forward for now
//     // < 0: no real soln exists => return -1
//     return (discriminant >= 0) ? (-b - std::sqrt(discriminant)) / (2 * a) : -1.0;
// }
// note: decided to remove this abstraction as extra copy operation needed here
// cant use move as that would re
// color normal_to_rgb(const vec3& normal) {
//     // every component needs to
//         // * 0.5
//         // + 0.5
//     return 0.5 * color{normal.x() + 1, normal.y() + 1, normal.z() + 1};
// }

color ray_color(const ray& ray, const hittable& world) {
    // hit
    hit_record record;
    if (world.hit(ray, 0, inifinity, record)) {
        return 0.5 * (record.normal + color{1,1,1});
    }

    // didnt hit
    vec3 unit_direction = unit_vector(ray.direction());
    double a = 0.5 * (unit_direction.y() + 1);  // because the values can go negative && u want it to be within
    color white_color{1, 1, 1};
    color blue_color(0.5, 0.7, 1.0);
    return (1 - a) * white_color + a * blue_color;

    // TODO: DEBUGGING
    // if (unit_direction.y() > 0.5) {
    //     // breakpoint 
    //     std::clog << unit_direction.y() << '\n';
    // }
}

int main() {
    // IMAGE
    // int image_width = 256;
    // int image_height = 256;
    auto aspect_ratio = 16.0 / 9.0;
    int image_width = 400;

    // image height
    int image_height = int(image_width / aspect_ratio);
    image_height = image_height > 1 ? image_height : 1; // image_height if image_height > 1 else 1

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
    vec3 viewport_u{viewport_width, 0, 0}; // left to right vector
    vec3 viewport_v{0, -viewport_height, 0}; // top to down vector

    // viewport delta vectors
    // vec3 pixel_delta_u{viewport_width / image_width, 0, 0}; // My attempt => better way below
    vec3 pixel_delta_u = viewport_u / image_width;
    vec3 pixel_delta_v = viewport_v / image_height;

    // calc location of upper left px
    // auto viewport_upper_left = camera_center - viewport_u / 2 - viewport_v / 2; // WRONG need to minus focal_length
        // focal_length is distance between camera & viewport
        // -Z => goes into the screen away from u
        // +Z => goes comes out of the screen toward u
    auto viewport_upper_left = camera_center - viewport_u / 2 - viewport_v / 2 - vec3{0, 0, focal_length};
    auto pixel_upper_left_loc = viewport_upper_left + 0.5 * pixel_delta_u + 0.5 * pixel_delta_u;  // PLUS coz they are going in the direction u want

    // RENDER IMG
    // mew gradient image
        // => this basically shoots a ray for every px in the img
        // => each px moves by a delta (could be less than 1 unit => making it heigher resolution)
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    for (int i = 0; i < image_height; i++) {
        // progress indicator: start + intermediate
        std::clog << "\rScanlines remaining:" << (image_height - i) << " / " << image_height << ' ' << std::flush;
        for (int j = 0; j < image_width; j++) {
            // get the next pixel center (because we are rendering px by px)
                // row: i && v
                // col: j && u
            point3 pixel_center = pixel_upper_left_loc + i * pixel_delta_v + j * pixel_delta_u;

            // ray direction?
            vec3 ray_direction = pixel_center - camera_center;  // its how the ray would be projected from the camera to the viewport

            // create ray
            ray ray{camera_center, ray_direction}; // could potentially make ray_direction a unit vector but this currently is just faster code for now
            // get the ray's color
            color pixel_color = ray_color(ray, world); // include the world
            // paint the image
            write_color(std::cout, pixel_color);
        }
    }
    // progress indicator: end
    std::clog << "\rdone.                      \n";

    // old image
    // std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    // for (int i = 0; i < image_height; i++) {
    //     // progress indicator: start + intermediate
        // std::clog << "\rScanlines remaining:" << (image_height - i) << " / " << image_height << ' ' << std::flush;

    //     for (int j = 0; j < image_width; j++) {
    //         // create pixel's color
    //         color pixel_color{double(j) / (image_width - 1), double(i) / (image_height - 1), 0.0};
    //         // print color
    //         write_color(std::cout, pixel_color);

    //     }
    // }
    // progress indicator: end
    // std::clog << "\rdone.                      \n";
}