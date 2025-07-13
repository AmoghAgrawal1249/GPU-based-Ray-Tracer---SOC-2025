#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"


using color = vec3;

void write_color(std::ostream& out, const color& pixel_color) {
    auto r = pixel_color[0];
    auto g = pixel_color[1];
    auto b = pixel_color[2];

    // Translate the [0,1] component values to the byte range [0,255].
    int rbyte = int(255.999f * r);
    int gbyte = int(255.999f * g);
    int bbyte = int(255.999f * b);

    // Write out the pixel color components.
    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}

#endif