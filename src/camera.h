#ifndef CAMERA_H
#define CAMERA_H

#include <cmath>
#include "color.h"
#include "hittable.h"
#include "raytracer_common.h"
#include "vec3.h"

#include "material.h" // camera is technically the "biggest" header for main.cpp

class camera {
public:
    double aspect_ratio = 1.0;
    int image_width = 100;
    int samples_per_pixel = 10; // number of random samples for each pixel (default=10)
    int max_depth = 10; // max num of ray bounces into scene

    double vfov = 90; // default vertical field of view (view angle)
    point3 lookfrom = point3(0.0, 0.0, 0.0);
    point3 lookat = point3(0.0, 0.0, -1.0);
    point3 vup = point3(0.0, 1.0, 0.0);

    
    
    void render(const hittable& world) {
        // called first to commit values for render
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
    // note that private members are set here to allow render to use them later after initialize
    int image_height;
    double pixel_samples_scale; // scale factor for a sum of pixel samples => declared & calculated in private coz user doesnt need to know && should reduce render time (best effort to calculate everythin in initialize first)
    point3 camera_center;
    point3 pixel_upper_left_loc;
    vec3 pixel_delta_u;
    vec3 pixel_delta_v;

    // camera frame basis vectors
    vec3 u, v, w;
    
    // initialize is private as its invoked internally by render()
    void initialize() {
        // image height (if image_height > 1 else 1)
        image_height = int(image_width / aspect_ratio);
        image_height = image_height > 1 ? image_height : 1;

        pixel_samples_scale = 1.0 / samples_per_pixel;

        // old: looks from origin
        // camera_center = point3{0.0,0.0,0.0}; // {} prevents type narrowing i.e. if point3 expects int, but {0.5, 0, 0} was provided

        // new: looks froms `lookfrom`
        camera_center = lookfrom;

        // CAMERA
        // old: arbitrary focal length
        // auto focal_length = 1.0;

        // new: determine viewport dimensions 
        double focal_length = (lookfrom - lookat).length();

        // viewport
        // previously where viewport was fixed at 2.0 height
        // auto viewport_height = 2.0;

        // new way of determining viewport via vfov
        double theta = degrees_to_radians(vfov);
        double h = std::tan(theta / 2);
        double viewport_height = 2 * h * focal_length;
        double viewport_width = viewport_height * (double(image_width) / image_height);

        // old: arbitrary viewport vectors which are aligned with x & y axises
        // vec3 viewport_u{viewport_width, 0, 0};
        // vec3 viewport_v{0, -viewport_height, 0};

        // new: viewport vectors using u & v vectors of the camera
        // calculate basis vectors for camera
        w = unit_vector(lookfrom - lookat);
        u = unit_vector(cross(vup, w));
        v = cross(w, u);

        vec3 viewport_u = viewport_width * u;
        vec3 viewport_v = viewport_height * -v;

        // viewport delta vectors
        pixel_delta_u = viewport_u / image_width;
        pixel_delta_v = viewport_v / image_height;

        // old: calc location of upper left px => arbitrary camera direction used
        // auto viewport_upper_left = camera_center - viewport_u / 2 - viewport_v / 2 - vec3{0, 0, focal_length};

        // new: calc location of upper left px => use w to know where the camera direction is
        auto viewport_upper_left = camera_center - (focal_length * w) - viewport_u / 2 - viewport_v / 2;
        pixel_upper_left_loc = viewport_upper_left + 0.5 * pixel_delta_u + 0.5 * pixel_delta_v;
    }

    // moved from main.cpp
    color ray_color(const ray& r, int depth, const hittable& world) const {

        // check depth
        if (depth <= 0) {
            return color(0.0,0.0,0.0); // no value added (no color basically )
        }

        // hit
        hit_record record;
        // set interval to 0.001 instead of 0 to ignore very small values when hitting a surface
        if (world.hit(r, interval(0.001, infinity), record)) {
            // hit hittable's material
            ray scattered;
            color attenuation;
            // if the hittable material is not default (only the parent's material returns false & doesnt scatter)
            // we use record's material because it hits a different material at every different record
            if (record.mat->scatter(r, record, attenuation, scattered)) {
                // place the scattered ray 
                return attenuation * ray_color(scattered, depth-1, world);
            }

            // else just return 0 color at the end => 0 color is white
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
        // create / construct a camerea ray originating from the origin & directed at randomly sampled point
        // point is around the pixel location (i, j)
        // exact ray coordinate = (i, j) + 0.5 + sample square => hence sameple square needs to be within the range [-0.5, +0.5]
        vec3 offset = sample_square();
        point3 pixel_sample = pixel_upper_left_loc + ((j + offset.x()) * pixel_delta_u) + ((i + offset.y()) * pixel_delta_v);

        point3 ray_origin = camera_center;
        vec3 ray_direction = pixel_sample - ray_origin;

        return ray(ray_origin, ray_direction);
    }

    vec3 sample_square() const {
        // returns vector to a random point in the [-.5,-.5] to [+.5,+.5] unit square
        return vec3(random_double() - 0.5, random_double() - 0.5, 0);
    }
};

#endif