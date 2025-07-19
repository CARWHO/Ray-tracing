#ifndef COLOUR_H
#define COLOUR_H

#include "vec3.h"
#include "interval.h"

using colour = vec3;

inline double linear_to_gamma(double linear_component) {
    if (linear_component > 0)
        return std::sqrt(linear_component);

    return 0;
}

void write_colour(std::ostream& out, const colour& pixel_colour) {
    auto r = pixel_colour.x();
    auto g = pixel_colour.y();
    auto b = pixel_colour.z();

    r = linear_to_gamma(r);
    g = linear_to_gamma(g);
    b = linear_to_gamma(b);

    static const interval intensity(0.000, 0.999);
    int r_byte = int(256 * intensity.clamp(r));
    int g_byte = int(256 * intensity.clamp(g));
    int b_byte = int(256 * intensity.clamp(b));

    out << r_byte << ' ' << g_byte << ' ' << b_byte << '\n';
}

#endif