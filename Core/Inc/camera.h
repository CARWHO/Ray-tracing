#ifndef CAMERA_H
#define CAMERA_H

#include "../Inc/hittable.h"
#include "../Inc/vec3.h"
#include "../Inc/material.h"  

class camera {
    public:

        double  aspect_ratio = 1.0;
        int image_width = 400;
        int samples_per_pixel = 10;
        int max_depth = 10;

        double vfov = 90;
        point3 lookfrom = point3(0,0,0);
        point3 lookat = point3(0,0,-1);
        point3 vup = vec3(0,1,0);

        double defocus_angle = 0;
        double focus_dist = 10;

        void render(const hittable& world) {
            initialze();
                // print p3, then a new line, print image width, then a space, then image_height, then a new line. print 255 then another new line.
            std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

            for (int i = 0; i < image_height; i++) {
                std::clog << "\rScanlines remaining:" << (image_height - i) << ' ' << std::flush;

                for (int j = 0; j < image_width; j++) {
                    colour pixel_colour(0,0,0);
                    for (int sample = 0; sample < samples_per_pixel; sample++) {
                        ray r = get_ray(i,j);
                        pixel_colour += ray_colour(r,max_depth,world);
                    }
                    write_colour(std::cout, pixel_samples_scale * pixel_colour);
                }
            }
            std::clog << "\r Completed.                \n";
        }

    private:

        int image_height;
        double pixel_samples_scale;

        point3 camera_center;
        point3 pixel00_loc;
        point3 v_delta;
        point3 u_delta;
        vec3 u, v, w;
        vec3 defocus_disc_u;
        vec3 defocus_disc_v;

        void initialze() {

            image_height = int(image_width / aspect_ratio);
            if (image_height < 1) {
                image_height = 1;
            } 

            pixel_samples_scale = 1.0 / samples_per_pixel;
            
            camera_center = lookfrom;

            auto theta = degrees_to_radians(vfov);
            auto h = std::tan(theta/2);
            
            auto viewport_height = 2 * h * focus_dist;
            auto viewport_width = viewport_height * (double(image_width)/image_height);

            w = unit_vector(lookfrom - lookat);
            u = unit_vector(cross(vup, w));
            v = cross(w,u);

            vec3 viewport_u = viewport_width * u;
            vec3 viewport_v = viewport_height * -v;

            v_delta = viewport_v/image_height;
            u_delta = viewport_u/image_width;

            auto viewport_upper_left = camera_center - (focus_dist * w) - viewport_u/2 - viewport_v/2;
            pixel00_loc = viewport_upper_left + 0.5 * (v_delta + u_delta);

            auto defocus_radius = focus_dist * std::tan(degrees_to_radians(defocus_angle/2));
            defocus_disc_u = u * defocus_radius;
            defocus_disc_v = v * defocus_radius;
        }

        ray get_ray(int i, int j) const {
            auto offset = sample_square();
            auto pixel_sample = pixel00_loc + ((j + offset.x()) * u_delta) + ((i + offset.y()) * v_delta);

            decltype(camera_center) ray_origin; // maybe wrong?
            if (defocus_angle <= 0) {
                ray_origin = camera_center;
            } else {
                ray_origin = defocus_disk_sample();
            }

            auto ray_direction = pixel_sample - ray_origin;

            return ray(ray_origin, ray_direction);
        }

        vec3 sample_square() const {
            return vec3(random_double() - 0.5, random_double() - 0.5, 0);
        }

        point3 defocus_disk_sample() const {
            auto p = random_in_unit_disc();
            return camera_center + (p[0] * defocus_disc_u) + (p[1] * defocus_disc_v);
        }

        colour ray_colour(const ray& r, int depth, const hittable& world) const {
            if (depth <= 0) {
                return colour(0,0,0);
            }

            hit_record rec;

            if (world.hit(r,interval(0.001,inf),rec)) {
                ray scattered;
                colour attenuation;
                if (rec.mat->scatter(r,rec,attenuation,scattered)) {
                    return attenuation * ray_colour(scattered, depth-1, world);
                }
                return colour(0,0,0);
            }

            vec3 unit_direction = unit_vector(r.direction());
            auto a = 0.5*((unit_direction.y()) + 1.0);
            return (1.0-a) * colour(1.0,1.0,1.0) + a * colour(0.5,0.7,1.0);
        }
};

#endif
