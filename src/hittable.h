#ifndef HITTABLE_H
#define HITTABLE_H

// forward delcaration
    // cpp has no class hoisting
    // forward declares the class so that current header can use it first & tells compiler to trust that definition will be provided later on
class material;

class hit_record {
public:
    point3 p;
    vec3 normal;
    shared_ptr<material> mat; // forward declared
    double t;
    bool front_face;

    // set face based on: ray & outward normal (normal pointing outwards)
    void set_face_normal(const ray& ray, vec3& unit_outward_normal) {
        front_face = dot(ray.direction(), unit_outward_normal) < 0;
        // point normal in opp direction if inside
        normal = front_face ? unit_outward_normal : -unit_outward_normal;
    }
};

class hittable {
public:
    virtual ~hittable() = default;

    /**
     * @brief hit() takes in a ray & returns if it hits the "hittable".
     */
    virtual bool hit(const ray& ray, interval ray_t, hit_record& record) const = 0;
};

#endif