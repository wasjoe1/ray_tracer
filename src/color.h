#ifndef COLOR_H
#define COLOR_H

using color = vec3;

// ODR one definition rule => a function can only be defined in your entire program once
    // technically putting a function definition in header files is not good practice
    // u dk if another .cpp or .h file will declare the same function
    // (does not protect function from being defined in multiple .cpp files!!)

// void write_color(std::ostream& out, const color& pixel_color);
// placed definition in the .cpp file
void write_color(std::ostream& out, const color& pixel_color) {
    // in ray tracing, we use normalized color values (x, y & z all contain fractions [0,1] )
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    // convert values to byte range [0, 255]
    int rbyte = int(255.999 * r); // normalized values translated here
    int gbyte = int(255.999 * g);
    int bbyte = int(255.999 * b);

    out << rbyte << ' ' << gbyte << ' ' << bbyte << ' ' << '\n';
}

#endif