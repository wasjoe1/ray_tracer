// unlike function definition, its okay for multiple TUs to have the same class definitions
    // class defn => type definition; compiler doesnt generate any actual machine instructions
    // function defn => executable code; contains instructions to be executed
// HOWEVER, cpp forbids multiple same class defn in the SAME translation unit
    // so, multiple TUs can share same class defn
    // BUT, 1 TU can only have 1 of that class defn
    
// just need to change the ray class in the header here
#ifndef RAY_H
#define RAY_H

#include "vec3.h"
class ray {
public:
    ray() {}
    ray(const point3& origin, const vec3& direction)
        : orig(origin), dir(direction) {}  // always take in the reference & if u dont plan to change it, use const

    // return private vars; return const reference (read-only view of OG data)
        // if return copy, copy operation
    const point3& origin() const { return orig; }
    const vec3& direction() const { return dir; }

    point3 at(double t) const {
        return orig + (t * dir);
    }
    
private:
    point3 orig;
    vec3 dir;
};

#endif