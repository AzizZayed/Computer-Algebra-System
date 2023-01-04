//
// Created by Abd-El-Aziz Zayed on 2022-12-31.
//

#ifndef COMPUTERALGEBRASYSTEM_GRID_H
#define COMPUTERALGEBRASYSTEM_GRID_H

#include "metal_math.h"
#include "metal_types.h"
#include <cstdint>

class Grid {
public:
    const uint32_t RESOLUTION = 100;
    const uint32_t WIDTH = RESOLUTION + 1;
    const uint32_t indexCount = RESOLUTION * RESOLUTION * 6;
    const uint32_t vertexCount = WIDTH * WIDTH;

    double yOrigin = 0.0;

    double xMin = -1.0;
    double xMax = 1.0;
    double yMin = -1.0;
    double yMax = 1.0;
    double zMin = -1.0;
    double zMax = 1.0;

    double xRotation = -M_PI_2;
    double zRotation = 0.0;

    const double maxXRotation = M_PI;
    const double maxZRotation = 2 * M_PI;

    double xLength() const {
        return xMax - xMin;
    }

    double yLength() const {
        return yMax - yMin;
    }

    double zLength() const {
        return zMax - zMin;
    }

    double xStep() const {
        return xLength() / RESOLUTION;
    }

    double yStep() const {
        return yLength() / RESOLUTION;
    }

    void scale(double factor, double damping = 0.05) {
        double avg = (xLength() + yLength() + zLength()) / 3.0;
        factor *= damping * avg;

        if (xMin < xMax && yMin < yMax) {
            xMin -= factor;
            yMin -= factor;
            //            zMin -= factor;
            xMax += factor;
            yMax += factor;
            //            zMax += factor;
        }
    }

    void reset() {
        yOrigin = 0.0;

        xMin = -1.0;
        xMax = 1.0;
        yMin = -1.0;
        yMax = 1.0;
        zMin = -1.0;
        zMax = 1.0;

        xRotation = -M_PI_2;
        zRotation = 0.0;
    }

    void raise(double dy) {
        yOrigin += dy;
    }

    void rotate(double x, double z, double damping = 0.5) {
        xRotation += x * damping;
        zRotation += z * damping;

        if (xRotation > maxXRotation) {
            xRotation += -2 * maxXRotation;
        } else if (xRotation < -maxXRotation) {
            xRotation += 2 * maxXRotation;
        }

        if (zRotation > maxZRotation) {
            zRotation -= maxZRotation;
        } else if (zRotation < -maxZRotation) {
            zRotation += maxZRotation;
        }
    }

    Transform transform() const {
        double z = -2.0;
        double scale = 1.00;
        return {
                math::translate(0, yOrigin, z),
                math::xRotate(-xRotation) * math::zRotate(-zRotation),
                math::scale(scale / xLength(), scale / yLength(), scale / zLength())};
    }
};

#endif//COMPUTERALGEBRASYSTEM_GRID_H
