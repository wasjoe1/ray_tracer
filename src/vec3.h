#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include<iostream>

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

    // const vec3 v;
    double operator[](int i) const { return e[i]; } // this means u return a copy of the value in the array memory in the obj
    // vec3 v;
    double& operator[](int i) { return e[i]; } // this means u return a reference to the array memory in the obj

    // "Arithmetic" operations
    // -vec
    vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
    // vec += vec2
    vec3& operator+=(const vec3& v) {
        // vector v passed in should not be changed, hence const
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        return *this; // return a reference to the obj
    }
    // vec *= vec2
    vec3& operator*=(double t) {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this; // return a reference to the obj
    }
    // vec /= vec2
    vec3& operator/=(double t) {
        return *this *= 1/t; // just multiply everythign by 1/t
    }

    // length
    double length_squared() const {
        return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
    }
    double length() const {
        return std::sqrt(length_squared()); // euclidean length (L2 norm)
    }
};

using point3 = vec3;

// ostream
inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2]; // doesnt add \n
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

#endif