#ifndef HITTABLE_H
#define HITTABLE_H

class hit_record {
public:
    point3 p;
    vec3 normal;
    double t;
    // side of surface; front face => ray is hitting the surface from the outside
    bool front_face;

    // method to set the face based on: ray & outward normal (normal pointing outwards)
    void set_face_normal(const ray& ray, vec3& unit_outward_normal) {
        // front face => opposite => 180degs => -ve
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
     * @param ray Ray contains origin & direction (doesnt have the t)
     * @param ray_tmax
     * @param ray_tmin
     * @param record Contains t (exact distance where the crash happened) & p (exact point of crash) & normal (direction of surface at exact spot)
     */
    virtual bool hit(const ray& ray, double ray_tmin, double ray_tmax, hit_record& record) const = 0;
    // = 0 mean? => abstract method
    // const => method that doesnt change the hittable object?
};

#endif