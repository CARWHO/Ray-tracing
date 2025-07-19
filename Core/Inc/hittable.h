#ifndef HITTABLE_H
#define HITTABLE_H

#include "../Inc/ray.h"
#include "../Inc/RT_main.h"

class material;

class hit_record {
    public:
        point3 p;
        vec3 normal;
        shared_ptr<material> mat;
        double t;
        bool front_face;

        void set_face_normal(const ray& r, const vec3& outward_normal) {
            if (dot(r.direction(), outward_normal) < 0) {
                front_face = true;
            } else {
                front_face = false;
            }
            
            if (front_face) {
                normal = outward_normal;
            } else {
                normal = -outward_normal;
            }
        }
};

class hittable {
    public:
        virtual ~hittable() = default;
        virtual bool hit(const ray& r, interval ray_t, hit_record& rec) const = 0;
};

#endif