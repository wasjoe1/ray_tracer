#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"

#include <vector>

class hittable_list : public hittable {
public:
    std::vector<shared_ptr<hittable>> objects;

    hittable_list() {} // need to declare default constructor because we have a non-default constructor below
    hittable_list(shared_ptr<hittable> object) { add(object); }

    void clear() { objects.clear(); }

    void add(shared_ptr<hittable> object) {
        objects.push_back(object);
    }

    bool hit(const ray& ray, double ray_tmin, double ray_tmax, hit_record& record) const override {
        hit_record temp_record;
        bool hit_anything = false;
        double closest_so_far = ray_tmax;

        // assign an auto type for the object => will follow what the list of parent pointers provided though
        for (const auto& object : objects) {
            if (object->hit(ray, ray_tmin, closest_so_far, temp_record)) {
                hit_anything = true; // we did hit
                closest_so_far = temp_record.t;
                record = temp_record;
            }
        }
    }
};

#endif