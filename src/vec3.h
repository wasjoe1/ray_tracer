#ifndef VEC3_H
#define VEC3_H

#include "raytracer_common.h"
class vec3 {
public:
    double e[3];

    // 0. constructors
    vec3() : e{0, 0, 0} {}
    vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}

    // 1. getters
    double x() const { return e[0]; }
    double y() const { return e[1]; }
    double z() const { return e[2]; }

    // const vec3 v; => copy-ed value returned
    double operator[](int i) const { return e[i]; }
    // vec3 v; => reference returned
    double& operator[](int i) { return e[i]; }

    // "Arithmetic" operations
    // -vec
    vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
    // vec += vec2
    vec3& operator+=(const vec3& v) {
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        // return a reference to the obj
        return *this;
    }
    // vec *= vec2
    vec3& operator*=(double t) {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
    }
    // vec /= vec2
    vec3& operator/=(double t) {
        return *this *= 1/t;
    }

    // length
    double length_squared() const {
        return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
    }
    double length() const {
        // euclidean length (L2 norm)
        return std::sqrt(length_squared());
    }

    // random unit vector
        // static member variable => (1) inline (2) inline (3) defined else where ELSE there will be duplicate symbol error
        // static member method => implicitly inline (same as non-static method) => only difference is the insertion of this pointer
    // why use static here? => coz its more efficient; no insertion of this variable
    static vec3 random() {
        return vec3(random_double(), random_double(), random_double());
    }
    static vec3 random(double min, double max) {
        return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
    }

    bool near_zero() const {
        // auto threshold = 1e-8f => this would have returned float because of the f suffix, but we are comparing double
        double threshold = 1e-8;
        // std::fabs => returns floating point absolute value, strips away -ve sign
        // std::abs => in old cpp, we cant use this as cmath did not allow for method overloading. but modern cpp updated std::abs to have specialized version for int, long, float, double, & long double

        // is true if vector is close to 0 for all components
        return (std::abs(e[0]) < threshold) && (std::abs(e[1]) < threshold) && (std::abs(e[2]) < threshold);
    }
};

using point3 = vec3;

// ostream
inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
    // dont add \n => let user decide
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

// + => image 5.0 + vec3 => 5.0 would not have the operator+ overloaded & will throw error
inline vec3 operator+(const vec3& u, const vec3& v) {
    return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

// -
inline vec3 operator-(const vec3& u, const vec3& v) {
    return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

// * (vec3, vec3)
inline vec3 operator*(const vec3& u, const vec3& v) {
    return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}
// * (vec3, double)
inline vec3 operator*(double t, const vec3& v) {
    return vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}
// * (double, vec3)
inline vec3 operator*(const vec3& v, double t) {
    return t * v;
}

// /
inline vec3 operator/(const vec3& v, double t) {
    return (1/t) * v;
}

// dot
inline double dot(const vec3& u, const vec3& v) {
    return (u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2]);
}

// cross
inline vec3 cross(const vec3& u, const vec3& v) {
    return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

// unit_vector
inline vec3 unit_vector(const vec3& v) {
    return v / v.length();
}

inline vec3 random_unit_vector() {
    // generates a random unit vector inside a unit sphere
    while (1) {
        vec3 random_vector = vec3::random(-1, 1); // vector components can be anywhere between -1 to 1
        double random_vector_squared_length = random_vector.length_squared(); // max length of vector can only be 1, squared of 1 is still 1 => max squared length is still 1

        // ensure no underflow error THEN check for max length
        if (1e-160 < random_vector_squared_length && random_vector_squared_length <= 1) {
            // plain sqrt is allowed even though we never declared it in global namespace because: https://stackoverflow.com/questions/16518210/sqrt-is-not-a-member-of-std
                // <cxxx...> headers are guaranteed to have standard names in std namespace & optionally provide in globalnamespace
                // in this case, it was <cmath>
            return random_vector / sqrt(random_vector_squared_length);
        }
    }
}

inline vec3 random_on_hemisphere(const vec3& normal) {
    vec3 on_unit_sphere = random_unit_vector();
    // return the unit vector in the correct hemisphere
    return dot(on_unit_sphere, normal) > 0.0 ? on_unit_sphere : -on_unit_sphere;
}

inline vec3 reflect(const vec3& v, const vec3& n) {
    // reflect the given vector about the normal vector
    return v - 2 * dot(v,n) * n;
}

inline vec3 refract(const vec3& uv, const vec3& n, double etai_over_etat) {
    double cos_theta = std::fmin(dot(-uv, n), 1.0);
    vec3 r_out_prep = etai_over_etat * (uv + cos_theta * n);
    vec3 r_out_parallel = -std::sqrt(std::fabs(1.0 - r_out_prep.length_squared())) * n;
    return r_out_parallel + r_out_prep;
}

inline vec3 random_in_unit_disk() {
    while (true) {
        vec3 p = vec3(random_double(-1.0, 1), random_double(-1.0, 1), 0.0);
        if (p.length_squared() < 1) { return p; }
    }
}

#endif