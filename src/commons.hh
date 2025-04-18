#ifndef COMMONS_H
#define COMMONS_H

// referred to as rtweekend in book
#include <cmath>
#include <random>
#include <iostream>
#include <limits>
#include <memory>

// Std usings
using std::make_shared;
using std::shared_ptr;

// Constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

//Utility funcs

inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

// [0, 1)
inline double random_double() {
    static std::uniform_real_distribution<double>distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

// [min, max)
inline double random_double(double min, double max) {
    return min + (max-min)*random_double();
}

// Common headers

#include "color.hh"
#include "interval.hh"
#include "ray.hh"
#include "vec3.hh"

#endif