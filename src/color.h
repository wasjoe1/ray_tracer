#ifndef COLOR_H
#define COLOR_H

#include <cmath>
using color = vec3;

inline double linear_to_gamma(double linear_component) {
    return linear_component > 0 ? std::sqrt(linear_component) : 0;
}

void write_color(std::ostream& out, const color& pixel_color) {
    // normalized color values (x, y & z all contain fractions [0,1])
    double r = pixel_color.x();
    double g = pixel_color.y();
    double b = pixel_color.z();

    // apply linear gamma transformation
    r = linear_to_gamma(r);
    g = linear_to_gamma(g);
    b = linear_to_gamma(b);


    // interval used to clamp intensity of each component
    static const interval intensity(0.000, 0.999);
    
    // convert values to byte range [0, 255]
    int rbyte = int(256 * intensity.clamp(r));
    int gbyte = int(256 * intensity.clamp(g));
    int bbyte = int(256 * intensity.clamp(b));

    out << rbyte << ' ' << gbyte << ' ' << bbyte << ' ' << '\n';
}
#endif