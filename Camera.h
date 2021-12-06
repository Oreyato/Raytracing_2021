#ifndef CAMERA_H
#define CAMERA_H

#include "Utility.h"
#include "Vec3.h"
#include "Ray.h"

class Camera {
    private:
        Vec3 mOrigin;
        Vec3 mLowerLeftCorner;
        Vec3 mHorizontal;
        Vec3 mVertical;
        Vec3 mU, mV, mW;
        double mLensRadius;

    public:
        Camera(Vec3 lookfrom, Vec3 lookAt, Vec3 vup, double vertFov, double aspectRatio, double aperture, double focusDistance) {
            double theta = DegreesToRadians(vertFov);
            double height = tan(theta/2.0);
            double viewportHeight = 2.0 * height;
            double viewportWidth = aspectRatio*viewportHeight; 

            mW = unitVector(lookfrom - lookAt);
            mU = unitVector(cross(vup, mW));
            mV = cross(mW, mU);

            mOrigin = lookfrom;
            mHorizontal = focusDistance * viewportWidth * mU;
            mVertical = focusDistance * viewportHeight * mV;
            mLowerLeftCorner = mOrigin - mHorizontal / 2 - mVertical / 2 - focusDistance * mW;
        }

        Ray GetRay(double s, double t) const {
            // Generating sample rays from inside a disk centered at the lookfrom point
            // Larger the radius, greater the focus blur
            Vec3 raysfromDisk = mLensRadius * RandomInUnitDisk();
            Vec3 offset = mU * raysfromDisk.x() + mV * raysfromDisk.y(); 

            return Ray(mOrigin + offset, mLowerLeftCorner + s*mHorizontal + t*mVertical - mOrigin - offset);
        }
};

#endif //CAMERA_H