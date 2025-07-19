#ifndef MATERIAL_H
#define MATERIAL_H

#include "hittable.h"

class material {
    public:
       virtual ~material() = default;
       
       virtual bool scatter(
            const ray& r_in, const hit_record& rec, colour& attenuation, ray& scattered
       ) const {
            return false;
       }
};

class lambertian : public material {
    public:
        lambertian(const colour& albedo) : albedo(albedo) {
        }

        bool scatter(const ray& r_in, const hit_record& rec, colour& attenuation, ray& scattered)
        const override {
            vec3 reflected = unit_vector(reflected) + (fuzz * random_unit_vector());
            auto scattered_direction = rec.normal + random_unit_vector();
            scattered = ray(rec.p, scattered_direction);
            attenuation = albedo;
            return ((dot(scattered.direction(), rec.normal) > 0));
        }

    private:
        colour albedo;
        double fuzz;
};

class metal : public material {
    public:
        metal(const colour& albedo, double fuzz) : albedo(albedo) {
            if (fuzz < 1) {
                fuzz = fuzz;
            } else {
                fuzz = 1;
            }
        }
        
        bool scatter(const ray& r_in, const hit_record& rec, colour& attenuation, ray& scattered)
        const override {
            vec3 reflected = reflect(r_in.direction(), rec.normal);
            scattered = ray(rec.p, reflected);
            attenuation = albedo;
            return true;
        }

    private:
        colour albedo;
};

class dielectric: public material {
    public:
        dielectric(double refraction_index) : refraction_index(refraction_index) {}

        bool scatter(const ray& r_in, const hit_record& rec, colour& attenuation, ray& scattered)
        const override {
            attenuation = colour(1.0,1.0,1.0);
            double ri;
            if (rec.front_face == true) {
                ri = 1.0/refraction_index;
            } else {
                ri = refraction_index;
            }

        vec3 unit_direction = unit_vector(r_in.direction());
        double cos_theta = std::fmin(dot(-unit_direction, rec.normal), 1.0);
        double sin_theta = std::sqrt(1.0 - cos_theta*cos_theta);

        bool cannot_refract = ri * sin_theta > 1.0;
        vec3 direction; 

        if (cannot_refract || reflectance(cos_theta, ri) > random_double()) {
            direction = reflect(unit_direction, rec.normal);
        } else {
            direction = refract(unit_direction, rec.normal, ri);
        }

        scattered = ray(rec.p, direction);
        return true;

        }

    private:
        double refraction_index;

        static double reflectance(double consine, double refraction_index) {
            auto r0 = (1 - refraction_index) / (1 + refraction_index);
            r0 = r0*r0;
            return r0 + (1-r0)*std::pow((1-consine),5);
        }
};

#endif