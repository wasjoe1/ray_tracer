#ifndef SPHERE_H
#define SPHERE_H

#include <cmath>

#include "hittable.h"

class sphere : public hittable {
public:
    sphere(const point3 center, double radius, shared_ptr<material> mat) : center{center}, radius{std::fmax(0, radius)}, mat{mat} {}

    bool hit(const ray& ray, interval ray_t, hit_record& record) const override {
        vec3 oc = center - ray.origin();
        double a = ray.direction().length_squared();
        double h = dot(ray.direction(), oc);
        double c = oc.length_squared() - radius * radius;

        // discriminant
        double discriminant = h * h - a * c;

        // if no real soln
        if (discriminant < 0) { return false; }

        // if yes real soln
        double sqrt_discriminant = std::sqrt(discriminant);

        // find nearest root => check minus first
        double root = (h - sqrt_discriminant) / a;
        if (!ray_t.surrounds(root)) {
            root = (h + sqrt_discriminant) / a;
            if (!ray_t.surrounds(root)) {
                return false;
            }
        }
        
        // root exists => set record
        record.t = root;
        record.p = ray.at(root);
        record.mat = mat;

        vec3 unit_outward_normal = (record.p - center) / radius;
        record.set_face_normal(ray, unit_outward_normal);

        return true;
    }

private:
    point3 center;
    double radius;
    shared_ptr<material> mat;
};
#endif