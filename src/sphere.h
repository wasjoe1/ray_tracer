#ifndef SPHERE_H
#define SPHERE_H

#include <cmath>

#include "hittable.h"

class sphere : public hittable {
public:
    // constructor
    sphere(const point3 center, double radius, shared_ptr<material> mat) : center{center}, radius{std::fmax(0, radius)}, mat{mat} {
        // TODO: init material pointer mat WHEN creating the sphere in the 3D scene
    }

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
        double root = (h - sqrt_discriminant) / a; // potential ERROR: if ray direction was 0, a will be 0; bad divide by 0 occurs here

        if (!ray_t.surrounds(root)) {
            root = (h + sqrt_discriminant) / a;
            if (!ray_t.surrounds(root)) {
                // doesnt exist
                return false;
            }
        }
        
        // root exists => set record
        record.t = root;
        record.p = ray.at(root);
        record.mat = mat; // record stores the material of sphere

        // add surface side determination => during hit calculation
        vec3 unit_outward_normal = (record.p - center) / radius;
        record.set_face_normal(ray, unit_outward_normal);

        return true;
    }

private:
    point3 center;
    double radius;
    shared_ptr<material> mat; // material of the sphere
};

#endif