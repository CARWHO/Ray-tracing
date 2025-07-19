#define HITTABLE_LIST_H
#ifdef HITTABLE_LIST_H

#include "RT_main.h"
#include "hittable.h"

#include <memory>
#include <vector>

class hittable_list : public hittable {
    public:
        std::vector<shared_ptr<hittable>> objects;

        hittable_list() {}
        hittable_list(shared_ptr<hittable> object) { add(object); }

        void clear() { objects.clear(); }

        void add(shared_ptr<hittable> object) {
            objects.push_back(object);
        }

    bool hit(const ray& r, interval ray_t, hit_record& rec) const override {

        hit_record temp_rec;
        bool hit_something = false;
        auto closest_to_hit = ray_t.max;

        for (const auto& object : objects) {
            if (object->hit(r, interval(ray_t.min, closest_to_hit), temp_rec)) {
                hit_something = true;
                closest_to_hit = temp_rec.t;
                rec = temp_rec;
            }
        }

        return hit_something;
    }
};

#endif