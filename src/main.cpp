#include "color.h" // provides color
#include "ray.h"
#include "vec3.h"

#include<iostream>

color ray_color(const ray& r) {
    // return color{0,0,0}; sets it all to black

    // creating a lerp between 2 values => linear blend OR linear interpolation
    vec3 unit_direction = unit_vector(r.direction());
    double a = 0.5 * (unit_direction.y() + 1);  // because the values can go negative && u want it to be within
    if (unit_direction.y() > 0.5) {
        std::clog << unit_direction.y() << '\n';
    }
    
    color white_color{1, 1, 1};
    color blue_color(0.5, 0.7, 1.0);

    return (1 - a) * white_color + a * blue_color;
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
            ray r{camera_center, ray_direction}; // could potentially make ray_direction a unit vector but this currently is just faster code for now
            // get the ray's color
            color pixel_color = ray_color(r);
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