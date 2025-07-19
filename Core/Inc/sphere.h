#ifndef SPHERE_H
#define SPHERE_H

#include "../Inc/hittable.h"
#include "../Inc/ray.h"
#include "../Inc/RT_main.h"

#include <cmath>

class sphere : public hittable {
    public:
        sphere(const point3& center, double radius, shared_ptr<material> mat) : center(center), radius(std::fmax(0,radius)), mat(mat) {}
        
        bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
            vec3 oc = center - r.origin();
            auto a = r.direction().length_squared();
            auto h = dot(r.direction(), oc);
            auto c = oc.length_squared() - radius * radius;

            auto disc = h*h - a*c;
            if (disc < 0) {
                return false;
            }

            auto sqrtd = (std::sqrt(disc));
            auto root = (h-sqrtd) / a;
            if (!ray_t.surrounds(root)) {
                root = (h + sqrtd) / a;
                if (!ray_t.surrounds(root)) {
                    root = (h + sqrtd) / a;
                }
                return false;
            }
            rec.mat = mat;
            rec.t = root;
            rec.p = r.at(rec.t);

            vec3 outward_normal = (rec.p - center) / radius;
            rec.set_face_normal(r,outward_normal);

            return true;
        }

    private:
        point3 center;
        double radius;
        shared_ptr<material> mat;
};

#endif