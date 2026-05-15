#ifndef COLOR_H
#define COLOR_H

#include <cmath>
using color = vec3;

inline double linear_to_gamma(double linear_component) {
    // use "gamma 2" as our transformation => power used when going from gamma space to linear space
        // take inverse of gamma 2 (1/gamma) => squareroot
    // also handle negative inputs robustly by checking if component is -ve
    if (linear_component > 0) {
        return std::sqrt(linear_component);
    }

    return 0;
}

void write_color(std::ostream& out, const color& pixel_color) {
    // in ray tracing, we use normalized color values (x, y & z all contain fractions [0,1])
    double r = pixel_color.x();
    double g = pixel_color.y();
    double b = pixel_color.z();

    // apply linear gamma transformation
    r = linear_to_gamma(r);
    g = linear_to_gamma(g);
    b = linear_to_gamma(b);


    // interval used to clamp intensity of each component
        // why 0.999 & not 1?
        // (refer to chapter_8 notes)
    static const interval intensity(0.000, 0.999);
    
    // convert values to byte range [0, 255]
    int rbyte = int(256 * intensity.clamp(r)); // normalized values translated here
    int gbyte = int(256 * intensity.clamp(g));
    int bbyte = int(256 * intensity.clamp(b));

    out << rbyte << ' ' << gbyte << ' ' << bbyte << ' ' << '\n';
}

// note that the function definition here might cause duplicate symbol errors at link time
    // its just because there is only 1 TU thats why this is fine
#endif