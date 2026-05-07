#include<iostream>

int main() {
    // set max IMAGE hieght & width
    int image_width = 256;
    int image_height = 256;

    // Create the image using ASCII characters
    // P3 means PPM format
        // color: use RGB
        // data: pixel stored as ASCII
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    // row
    for (int i = 0; i < image_height; i++) {
        std::clog << "\rScanlines remaining:" << (image_height - i) << " / " << image_height << ' ' << std::flush; // stream manipulator => doesnt print char, it triggers .flush method on the strean obj (can be used on std::clog, std::cout)
        // col
        for (int j = 0; j < image_width; j++) {
            auto r = double(j) / (image_width - 1); // 0 to 255
            auto g = double(i) / (image_height - 1); // why auto? style called AAA (almost always auto) => right side of the equals sign usually tells u exactly what the return type it (hence the explicit double would be redundant)
            auto b = 0.0; // double(i) cast => int / int = int; double / int = double

            int ir = int(255.999 * r); // to give it better rounding, we use 255.999
            int ig = int(255.999 * g);
            int ib = int(255.999 * b);

            std::cout << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }

    // std::clog is meant for logging & diagnostics
    std::clog << "\rdone.                      \n";
    // std::clog << "\rdone.                \n"; // try this, u cam see that it didnt "erase" enough characters
}