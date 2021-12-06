#ifndef COLOR_H
#define COLOR_H

#include <iostream>

#include "Utility.h"


void WriteColor(std::ostream &out, Vec3 pixelColor, int samplesPerPixel) {
    double r = pixelColor.x();
    double g = pixelColor.y();
    double b = pixelColor.z();

    // Divide the color by the number of samples
    double scale = 1.0 / samplesPerPixel;
    r = sqrt(scale*r);
    g = sqrt(scale*g);
    b = sqrt(scale*b);

    // Write the translated [0, 255] value of each color component
    out << static_cast<int>(255.999 * Clamp(r, 0.0, 0.999)) << ' '
        << static_cast<int>(255.999 * Clamp(g, 0.0, 0.999)) << ' '
        << static_cast<int>(255.999 * Clamp(b, 0.0, 0.999)) << '\n';
}

#endif //COLOR_H