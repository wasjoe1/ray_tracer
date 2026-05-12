#ifndef SPHERE_H
#define SPHERE_H

#include <cmath>

#include "hittable.h" // need hittable to inherit (sphere is subclass of hittable)

class sphere : public hittable {  // specifies access specifier of inheritance =>
public:
    // constructor => empty constructor
    sphere(const point3 center, double radius) : center{center}, radius{std::fmax(0, radius)} {}

    // hit => override hittable's hit method
    bool hit(const ray& ray, double ray_tmin, double ray_tmax, hit_record& record) const override {
        // const function => hit method should not alter the sphere, should just return the point of hitting
        // override from parent class

        // All variables required
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
        // (ray_tmin < root < ray_tmax) is not allowed in cpp!
            // cpp evaluates expression from left to right
            // (ray_tmin < root) will return 0 or 1 first
            // then compare it to ray_tmax
        if (root <= ray_tmin || ray_tmax <= root) {
            // minus not in range => check positive
            double root = (h + sqrt_discriminant) / a;
            if (root <= ray_tmin || ray_tmax <= root) {
                return false; // doesnt exist
            }
        }

        // root exists => set record
        record.t = root;
        record.p = ray.at(root);

        // record.normal = (record.p - center) / radius;
        // add surface side determination
        vec3 unit_outward_normal = (record.p - center) / radius;
        record.set_face_normal(ray, unit_outward_normal);

        return true;
    }

private:
    point3 center;
    double radius;
};

#endif