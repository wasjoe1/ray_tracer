#include "color.h"
#include<iostream>

void write_color(std::ostream& out, const color& pixel_color) {
    // in ray tracing, we use normalized color values (x, y & z all contain fractions [0,1] )
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    // convert values to byte range [0, 255]
    int rbyte = int(255.999 * r); // normalized values translated here
    int gbyte = int(255.999 * g);
    int bbyte = int(255.999 * b);

    // write out the pixle color components
    out << rbyte << ' ' << gbyte << ' ' << bbyte << ' ' << '\n';
}