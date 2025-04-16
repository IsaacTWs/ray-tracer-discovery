#ifndef COMMONS_H
#define COMMONS_H

// referred to as rtweekend in book
#include <cmath>
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

// Common headers

#include "color.hh"
#include "interval.hh"
#include "ray.hh"
#include "vec3.hh"

#endif