#ifndef COLOR_H
#define COLOR_H

#include "interval.hh"
#include "vec3.hh"


using Color = Vec3;

inline double liner_to_gamma(double linear_component) {
    if (linear_component > 0) {
        return std::sqrt(linear_component);
    }
    return 0;
}

void write_color(std::ostream& out, const Color& pixel_color) {
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    //apply linear to gamma transform for gamma 2
    r = liner_to_gamma(r);
    g = liner_to_gamma(g);
    b = liner_to_gamma(b);

    //convert range [0,1] -> [0, 255]
    static const Interval intensity(0.000, 0.999);
    int rbyte = int(256 * intensity.clamp(r));
    int gbyte = int(256 * intensity.clamp(g));
    int bbyte = int(256 * intensity.clamp(b));

    out << rbyte << ' ' << gbyte << ' ' << bbyte << "\n";
}

#endif