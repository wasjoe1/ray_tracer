#ifndef VEC3_H // checks if VEC3_H was defined, else define if and everything else
#define VEC3_H

#include <cmath>
#include<iostream>

class vec3 {
public:
    // e[3] ?? => what is this??
    double e[3]; // double array

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

    // const double operator[](int i) const { return e[i]; } // this means the double is constant? yes, but its redundant since it doesnt add any extra protection

    // just a REMINDER on const:
    // const int x = 1; // this means that the x's value cant be changed
    // ptrs
    // int a = 1;
    // const int* ptr1 = &a; // this means that the value in the memory is not changeable => cant reassign via *ptr1 = 2; BUT u can change the memory ptr1 points to?
    // int* const ptr2 = &a; // this is the opposite where the memory ptr2 cant be changed, but the value at the address can; *ptr2 = 2 is allowed but ptr2 = &b is not allowed

    // "Arithmetic" operations
    vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); } // unary operator => looks to the right (itself)
    vec3& operator+=(const vec3& v) { // binary operator => looks left for itself (this), & right (target vector; the argument)
        // vector v passed in should not be changed, hence const
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        return *this; // return a reference to the obj
    }
    vec3& operator*=(double t) {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this; // return a reference to the obj
    }
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

// point3 is just alias for vec3 (point3 is basically vec3)
using point3 = vec3;

// 2 things happening in the lines below:
    // 1. operator overload
    // 2. inline keyword => copy & paste the actual function into the locality im calling it
        // * performance optimization, typically CPU need to pause, jump to MEM address of function being called, run the function body code, then jump back to current code localation to continue execution
        // * but below functions are really small that jumping around takes bulk of the time compared to the actual execution

// * rule of thumb in cpp: if a function can be implemented using only the public interface of a class, it should be a member function
    // smaller classes keep class clean
    // makes class more modular??
    
// ostream
inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
    // best practice: dont add new line!
    // let user decide whether he/ she wants to have a newline
}
// this inline function means the compiler tries to eliminate this function entirely by replacing the function call with this function's body
// why not use define? (#define SQUARE(X)) becoz define is not type sage

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
// double was used here ,but some ray tracers use float