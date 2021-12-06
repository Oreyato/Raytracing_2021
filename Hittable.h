#ifndef HITTABLE_H
#define HITTABLE_H

#include "Ray.h"

class Material;

struct HitRecord {
    Vec3 p;
    Vec3 normal;
    double t;
    // Normal direction
    bool frontFace;
    // materialPtr will point to the material pointer of the sphere when it will be set up in main()
    shared_ptr<Material> materialPtr;

    inline void SetFaceNormal(const Ray& r, const Vec3& outwardNormal) {
        frontFace = dot(r.direction(), outwardNormal) < 0;
        normal = frontFace ? outwardNormal :-outwardNormal;
    }
};

class Hittable {
    public:
        virtual bool Hit(const Ray& r, double tMin, double tMax, HitRecord& rec) const = 0;
};

#endif