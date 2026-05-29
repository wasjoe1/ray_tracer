#ifndef RTCOMMON_H
#define RTCOMMON_H

#include <cmath>
#include <iostream>
#include <limits>
#include <memory>

using std::make_shared;
using std::shared_ptr;

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

#include <random>
inline double random_double() {
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator; // larger range of random values to choose from
    return distribution(generator);
}

// random real double in [min, max) => same as before
inline double random_double(double min, double max) {
    return min + (max - min) * random_double();
}

#include "interval.h"
#include "vec3.h"
#include "color.h"
#include "ray.h"
#endif