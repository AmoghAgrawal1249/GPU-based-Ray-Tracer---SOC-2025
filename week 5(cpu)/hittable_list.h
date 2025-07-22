#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"

#include <vector>



// Container for a list of hittable objects (the scene)
class hittable_list : public hittable {
  public:
    std::vector<shared_ptr<hittable>> objects;

    hittable_list() {}
    hittable_list(shared_ptr<hittable> object) { add(object); }

    void clear() { objects.clear(); }

    void add(shared_ptr<hittable> object) {
        objects.push_back(object);
    }

    // Returns true if any object is hit, filling record with closest hit
    bool hit(const ray& input_ray, interval ray_t, hit_record& record) const override {
        hit_record temp_record;
        bool hit_anything = false;
        auto closest_so_far = ray_t.max;

        for (const auto& object : objects) {
            if (object->hit(input_ray, interval(ray_t.min, closest_so_far), temp_record)) {
                hit_anything = true;
                closest_so_far = temp_record.hit_t;
                record = temp_record;
            }
        }

        return hit_anything;
    }
};

#endif