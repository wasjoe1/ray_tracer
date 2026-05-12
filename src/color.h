#ifndef COLOR_H
#define COLOR_H

using color = vec3;

// ODR one definition rule => a function can only be defined in your entire program once
    // technically putting a function definition in header files is not good practice
    // u dk if another .cpp or .h file will declare the same function
    // (does not protect function from being defined in multiple .cpp files!!)

void write_color(std::ostream& out, const color& pixel_color);
// placed definition in the .cpp file

#endif