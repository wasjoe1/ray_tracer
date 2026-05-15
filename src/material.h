#ifndef MATERIAL_H
#define MATERIAL_H

#include "hittable.h"
#include "vec3.h"

// parent: material
class material {
public:
    virtual ~material() = default;

    // =0 - pure virtual method
    // virtual bool scatter(...) const = 0;

    // default method
    virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const {
        // default is to return false;
        return false;
    }
};

// child 1: lambertian material
class lambertian : public material {
public:
    lambertian(const color& albedo) : albedo(albedo) {}

    bool scatter(const ray& r_in, const hit_record& record, color& attenuation, ray& scattered) const override {
        vec3 scatter_direction = record.normal + random_unit_vector();

        // accounts for 0 unit vectors which might cause NaN & inf errors
        if (scatter_direction.near_zero()) {
            scatter_direction = record.normal;
        }

        scattered = ray(record.p, scatter_direction);
        attenuation = albedo;
        return true;
    }

private:
    color albedo;
};

// child 1: lambertian material
class metal : public material {
public:
    metal(const color& albedo, double fuzz) : albedo(albedo), fuzz(fuzz < 1 ? fuzz : 1) {}

    bool scatter(const ray& r_in, const hit_record& record, color& attenuation, ray& scattered) const override {
        vec3 reflected = reflect(r_in.direction(), record.normal);

        // make it fuzzy => just deflect it abit using a random_unit vector
        reflected = unit_vector(reflected) + (fuzz * random_unit_vector());

        scattered = ray(record.p, reflected);
        attenuation = albedo;
        return true;
    }

private:
    color albedo;
    double fuzz; // cant be more 1
};

#endif