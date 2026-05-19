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

// child 2: metal material
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
    // cant be more than 1
    double fuzz;
};

class dielectric : public material {
public:
    dielectric(double m_refraction_index) : m_refraction_index(m_refraction_index) {}

    bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override {
        attenuation = color{1.0, 1.0, 1.0};
        double ri = rec.front_face ? (1.0 / m_refraction_index) : m_refraction_index;

        vec3 unit_direction = unit_vector(r_in.direction());
        double cos_theta = std::fmin(dot(-unit_direction, rec.normal), 1.0);
        double sin_theta = std::sqrt(1.0 - cos_theta*cos_theta);

        bool is_reflect = (ri * sin_theta > 1.0) || (reflectance(cos_theta, ri) > random_double());
        vec3 direction;
        direction = is_reflect ? reflect(unit_direction, rec.normal) : refract(unit_direction, rec.normal, ri);

        scattered = ray(rec.p, direction);
        return true;
    }

private:
    double m_refraction_index;

    static double reflectance(double cosine, double refraction_index) {
        // note that the refraction_index used here cant take in non-static variables
        double r0 = (1 - refraction_index) / (1 + refraction_index);
        r0 = r0 * r0;
        return r0 + (1-r0) * std::pow((1-cosine), 5);
    }
};

#endif