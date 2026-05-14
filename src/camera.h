#ifndef CAMERA_H
#define CAMERA_H

#include "color.h"
#include "hittable.h"

class camera {
public:
    // public variables provided by user (below are default values set)
    // values only initialized upon instantiation => since not static members
    double aspect_ratio = 1.0;
    int image_width = 100;
    int samples_per_pixel = 10; // number of random samples for each pixel (default=10)
    
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
                    pixel_color += ray_color(r, world);
                }
                write_color(std::cout, pixel_color * pixel_samples_scale);

                // OLD pixel color:
                // // next pixel center (we are rendering px by px)
                // point3 pixel_center = pixel_upper_left_loc + i * pixel_delta_v + j * pixel_delta_u;

                // // ray direction
                // vec3 ray_direction = pixel_center - camera_center;

                // // create ray
                // ray ray{camera_center, ray_direction};
                // // ray's color
                // color pixel_color = ray_color(ray, world);
                // // create image
                // write_color(std::cout, pixel_color);
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
    
    // initialize is private as its invoked internally by render()
    void initialize() {
        // something
        // image height
        image_height = int(image_width / aspect_ratio);
        // image_height if image_height > 1 else 1
        image_height = image_height > 1 ? image_height : 1;

        pixel_samples_scale = 1.0 / samples_per_pixel;

        camera_center = point3{0.0,0.0,0.0}; // {} prevents type narrowing i.e. if point3 expects int, but {0.5, 0, 0} was provided

        // CAMERA
        auto focal_length = 1.0;
        // viewport
        auto viewport_height = 2.0;
        auto viewport_width = viewport_height * (double(image_width) / image_height);
        
        // viewport vectors
        vec3 viewport_u{viewport_width, 0, 0};
        vec3 viewport_v{0, -viewport_height, 0};

        // viewport delta vectors
        pixel_delta_u = viewport_u / image_width;
        pixel_delta_v = viewport_v / image_height;

        // calc location of upper left px
        auto viewport_upper_left = camera_center - viewport_u / 2 - viewport_v / 2 - vec3{0, 0, focal_length};
        pixel_upper_left_loc = viewport_upper_left + 0.5 * pixel_delta_u + 0.5 * pixel_delta_v;
    }

    // moved from main.cpp
    color ray_color(const ray& ray, const hittable& world) const {
        // hit
        hit_record record;
        if (world.hit(ray, interval(0, infinity), record)) {
            return 0.5 * (record.normal + color{1,1,1});
        }

        // didnt hit
        vec3 unit_direction = unit_vector(ray.direction());
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