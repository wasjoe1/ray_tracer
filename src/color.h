#ifndef COLOR_H
#define COLOR_H

using color = vec3;

void write_color(std::ostream& out, const color& pixel_color) {
    // in ray tracing, we use normalized color values (x, y & z all contain fractions [0,1])
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

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