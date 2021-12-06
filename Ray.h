#ifndef RAY_H
#define RAY_H

#include "Vec3.h"

class Ray
{
    public:
        Vec3 mOrigin;
        Vec3 mDirection;

    public:
        Ray() {}
        Ray(const Vec3& origin, const Vec3& direction) { mOrigin = origin; mDirection = direction; }
        Vec3 origin() const { return mOrigin; }
        Vec3 direction() const { return mDirection; }
        Vec3 point_at_parameter(float t) const { return mOrigin + t*mDirection; }
};

#endif