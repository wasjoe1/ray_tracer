#ifndef HITTABLE_H
#define HITTABLE_H

// forward delcaration
class material;

class hit_record {
public:
    point3 p;
    vec3 normal;
    double t;
    bool front_face;

    // forward declared
    shared_ptr<material> mat;

    void set_face_normal(const ray& ray, vec3& unit_outward_normal) {
        front_face = dot(ray.direction(), unit_outward_normal) < 0;
        normal = front_face ? unit_outward_normal : -unit_outward_normal;
    }
};

class hittable {
public:
    virtual ~hittable() = default;

    virtual bool hit(const ray& ray, interval ray_t, hit_record& record) const = 0;
};

#endif