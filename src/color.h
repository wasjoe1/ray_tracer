#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"

#include <iostream>  // 2nd iosteam declared // has its own header guard
// => generally <iiosteam> has their own header guards (i.e. ifndef) => compiler will then skip it
// so why do we still include iostream when vec3.h already has `iostream`
// better for independence (if layer decided to only include vec3.h)

using color = vec3;

// ODR one definition rule => a function can only be defined in your entire program once
    // technically putting a function definition in header files is not good practice
    // u dk if another .cpp or .h file will declare the same function
    // (does not protect function from being defined in multiple .cpp files!!)

void write_color(std::ostream& out, const color& pixel_color);
// placed definition in the .cpp file

#endif