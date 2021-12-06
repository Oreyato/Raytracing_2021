#ifndef SPHERE_H
#define SPHERE_H

#include "Hittable.h"

class Sphere : public Hittable {
    public :
        Vec3 mCenter;
        double mRadius;
        shared_ptr<Material> mMatPtr;

    public :
        Sphere() {}
        Sphere(Vec3 center, double radius, shared_ptr<Material> mat) : mCenter(center), mRadius(radius), mMatPtr(mat) {};
        virtual bool Hit(const Ray& r, double tMin, double tMax, HitRecord& rec) const override;
};

bool Sphere::Hit(const Ray& r, double tMin, double tMax, HitRecord& rec) const {
    // b becomes half_b when considering b as 2h, implies this*
    Vec3 originToCenter = r.origin() - mCenter;
    double a = r.direction().squaredLength();
    double half_b = dot(originToCenter, r.direction());
    double c = originToCenter.squaredLength() - mRadius*mRadius;
    double delta = half_b*half_b - a*c;

    if (delta < 0) {
        return false;
    } 
    
    double sqrtDelta = sqrt(delta);

    // Find the nearest root that lies in the acceptable range
    // *Simplifies this
    double root = (-half_b - sqrtDelta) / a;
    if (root < tMin || tMax < root) {
        root = (-half_b + sqrtDelta) / a;
        
        if (root < tMin || tMax < root) {
            return false;    
        }
    }

    rec.t = root;
    rec.p = r.point_at_parameter(rec.t);
    Vec3 outwardNormal = (rec.p - mCenter) / mRadius;
    rec.SetFaceNormal(r, outwardNormal);
    rec.materialPtr = mMatPtr;

    return true;
}

#endif