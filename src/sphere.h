#ifndef SPHERE_H
#define SPHERE_H

#include <cmath>

#include "hittable.h"

class sphere : public hittable {
public:
    // constructor
    sphere(const point3 center, double radius) : center{center}, radius{std::fmax(0, radius)} {}

    // hit
    bool hit(const ray& ray, interval ray_t, hit_record& record) const override {
        // Variables required
        vec3 oc = center - ray.origin();
        double a = ray.direction().length_squared();
        double h = dot(ray.direction(), oc);
        double c = oc.length_squared() - radius * radius;

        // calc discriminant
        double discriminant = h * h - a * c;
        // if no real soln
        if (discriminant < 0) { return false; }

        // if yes real soln
        double sqrt_discriminant = std::sqrt(discriminant);
        // find nearest root => check minus first
        double root = (h - sqrt_discriminant) / a;

        if (!ray_t.surrounds(root)) {
            double root = (h + sqrt_discriminant) / a;
            if (!ray_t.surrounds(root)) {
                // doesnt exist
                return false;
            }
        }
        
        // root exists => set record
        record.t = root;
        record.p = ray.at(root);

        // add surface side determination => during hit calculation
        vec3 unit_outward_normal = (record.p - center) / radius;
        record.set_face_normal(ray, unit_outward_normal);

        return true;
    }

private:
    point3 center;
    double radius;
};

#endif