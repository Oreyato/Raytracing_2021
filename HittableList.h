#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "Hittable.h"

#include <memory>
#include <vector>

using std::shared_ptr; // -> a pointer to some allocated type | everytime you assign its value to another shared pointer, the reference count is incremented
using std::make_shared;

class HittableList : public Hittable {
    public:
        HittableList() {}
        HittableList(shared_ptr<Hittable> object) { Add(object); }

        void Clear() { objects.clear(); }
        void Add(shared_ptr<Hittable> object) { objects.push_back(object); }

        bool Hit(const Ray& r, double tMin, double tMax, HitRecord& rec) const override;

    public:  
        std::vector<shared_ptr<Hittable>> objects;
};

bool HittableList::Hit(const Ray& r, double tMin, double tMax, HitRecord& rec) const {
    HitRecord tempRec;
    bool hitAnything = false;
    double closestSoFar = tMax;

    for (const auto& object : objects) {
        if (object->Hit(r, tMin, closestSoFar, tempRec)) {
            hitAnything = true;
            closestSoFar = tempRec.t;
            rec = tempRec;
        }
    }

    return hitAnything;
}

#endif //HITTABLE_LIST_H