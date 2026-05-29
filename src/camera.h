#ifndef CAMERA_H
#define CAMERA_H

#include <cmath>
#include "color.h"
#include "hittable.h"
#include "raytracer_common.h"
#include "vec3.h"
#include "material.h"

class camera {
public:
    double aspect_ratio = 1.0;
    int image_width = 100;
    int samples_per_pixel = 10;
    int max_depth = 10;

    double vfov = 90;
    point3 lookfrom = point3(0.0, 0.0, 0.0);
    point3 lookat = point3(0.0, 0.0, -1.0);
    point3 vup = point3(0.0, 1.0, 0.0);

    double defocus_angle = 0;
    double focus_distance = 10;
    
    void render(const hittable& world) {
        initialize();

        // RENDER IMG
        std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
        for (int i = 0; i < image_height; i++) {
            // progress indicator: start + intermediate
            std::clog << "\rScanlines remaining:" << (image_height - i) << " / " << image_height << ' ' << std::flush;
            for (int j = 0; j < image_width; j++) {
                color pixel_color{0, 0, 0}; // start with 0 for each component
                for (int sample = 0; sample < samples_per_pixel; sample++) {
                    // accumulate all the colors of random samples
                    ray r = get_ray(i, j); // get random ray for the current (i, j) pixel
                    pixel_color += ray_color(r, max_depth, world); // add max_depth to ensure recursion doesnt EXPLODE
                }
                write_color(std::cout, pixel_color * pixel_samples_scale);
            }
        }
        // progress indicator: end
        std::clog << "\rdone.                      \n";
    }

private:
    int image_height;
    double pixel_samples_scale;
    point3 camera_center;
    point3 pixel_upper_left_loc;
    vec3 pixel_delta_u;
    vec3 pixel_delta_v;

    vec3 u, v, w;
    vec3 defocus_disk_u, defocus_disk_v;
    
    void initialize() {
        image_height = int(image_width / aspect_ratio);
        image_height = image_height > 1 ? image_height : 1;

        pixel_samples_scale = 1.0 / samples_per_pixel;

        // CAMERA
        camera_center = lookfrom;
        // determine viewport via vfov
        double theta = degrees_to_radians(vfov);
        double h = std::tan(theta / 2);
        double viewport_height = 2 * h * focus_distance;
        double viewport_width = viewport_height * (double(image_width) / image_height);

        // basis vectors for camera
        w = unit_vector(lookfrom - lookat);
        u = unit_vector(cross(vup, w));
        v = cross(w, u);

        vec3 viewport_u = viewport_width * u;
        vec3 viewport_v = viewport_height * -v;

        // viewport delta vectors
        pixel_delta_u = viewport_u / image_width;
        pixel_delta_v = viewport_v / image_height;

        // location of upper left px
        auto viewport_upper_left = camera_center - (focus_distance * w) - viewport_u / 2 - viewport_v / 2;
        pixel_upper_left_loc = viewport_upper_left + 0.5 * pixel_delta_u + 0.5 * pixel_delta_v;

        // defocus disk basis vectors
        double defocus_radius = focus_distance * std::tan(degrees_to_radians(defocus_angle / 2));
        defocus_disk_u = u * defocus_radius;
        defocus_disk_v = v * defocus_radius;
    }

    color ray_color(const ray& r, int depth, const hittable& world) const {
        // max depth
        if (depth <= 0) {
            return color(0.0,0.0,0.0);
        }

        // hit
        hit_record record;
        // set interval to 0.001 instead of 0 to ignore very small values when hitting a surface
        if (world.hit(r, interval(0.001, infinity), record)) {
            ray scattered;
            color attenuation;

            if (record.mat->scatter(r, record, attenuation, scattered)) {
                return attenuation * ray_color(scattered, depth-1, world);
            }

            return color(0.0, 0.0, 0.0);
        }

        // didnt hit
        vec3 unit_direction = unit_vector(r.direction());
        double a = 0.5 * (unit_direction.y() + 1);
        color white_color{1.0, 1.0, 1.0};
        color blue_color(0.5, 0.7, 1.0);
        return (1.0 - a) * white_color + a * blue_color;
    }

    ray get_ray(int i, int j) {
        vec3 offset = sample_square();
        point3 pixel_sample = pixel_upper_left_loc + ((j + offset.x()) * pixel_delta_u) + ((i + offset.y()) * pixel_delta_v);

        point3 ray_origin = (defocus_angle <= 0) ? camera_center : defocus_disk_sample();
        vec3 ray_direction = pixel_sample - ray_origin;
        return ray(ray_origin, ray_direction);
    }

    vec3 sample_square() const {
        // returns a random point in [-.5,-.5] to [+.5,+.5] unit square range
        return vec3(random_double() - 0.5, random_double() - 0.5, 0);
    }

    point3 defocus_disk_sample() const {
        vec3 p = random_in_unit_disk();
        return camera_center + (p[0] * defocus_disk_u) + (p[1] * defocus_disk_v);
    }
};

#endif