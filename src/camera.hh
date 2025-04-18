#ifndef CAMERA_H
#define CAMERA_H

#include "hittable.hh"

class Camera {
    public: 
        double aspect_ratio;
        int image_width;
        int samples_per_pixel;

        void render(const Hittable& world) {
            initialize();

            std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

            //Render pixels from top to bottom starting at (0,0)
            for(int i = 0; i < image_height; i++) {
                std::clog << "\rScanlines remaining: " << (image_height - i) << " " << std::flush;
                for(int j = 0; j < image_width; j++) {
                    Color pixel_color(0,0,0);
                    for(int sample = 0; sample < samples_per_pixel; sample++) {
                        Ray r = get_ray(j, i);
                        pixel_color += ray_color(r, world);
                    }
                    write_color(std::cout, pixel_samples_scale * pixel_color);
                }
             }
            std::clog << "\rDone.                     \n";
        }

    private:
        int image_height;
        double pixel_samples_scale;
        Point3 center;
        Point3 pixel_loc;
        Vec3 pixel_delta_u;
        Vec3 pixel_delta_v;        

        void initialize() {
            image_height = int(image_width / aspect_ratio);
            image_height = (image_height < 1) ? 1 : image_height;

            pixel_samples_scale = 1.0 / samples_per_pixel;

            center = Point3(0,0,0);

            auto focal_length = 1.0;
            auto viewport_height = 2.0;
            auto viewport_width = viewport_height * (double(image_width)/image_height);

            //find vectors across horizontal and down vertical viewport edges
            auto viewport_u = Vec3(viewport_width, 0, 0);
            auto viewport_v = Vec3(0, -viewport_height, 0);

            //find horizontal and vertical delta vectors from pixel to pixel
            pixel_delta_u = viewport_u/image_width;
            pixel_delta_v = viewport_v/image_height;

            //find location of upper left pixel
            auto viewport_upper_left = center - Vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
            pixel_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

        }

        Ray get_ray(int i, int j) const {
            // origin camera ray directed at randomly sampled point around pixel i,j

            auto offset = sample_square();
            auto pixel_sample = pixel_loc + 
                ((i + offset.x()) * pixel_delta_u) +
                ((j + offset.y()) * pixel_delta_v);

            auto ray_origin = center;
            auto ray_direction = pixel_sample - ray_origin;

            return Ray(ray_origin, ray_direction);

        }

        Vec3 sample_square() const {
            return Vec3(random_double() - 0.5, random_double() - 0.5, 0);
        }

        Color ray_color(const Ray& r, const Hittable& world) const {
            Hit_Record rec;
            if (world.hit(r, Interval(0, infinity), rec)) {
                return 0.5 * (rec.normal + Color(1,1,1));
            }
            // blendedVal = (1 - a) * start + a * end
            Vec3 unit_direction = unit_vector(r.direction());
            auto a = 0.5*(unit_direction.y() + 1.0);
            return (1.0 - a)*Color(1.0, 1.0, 1.0) + a*Color(0.5, 0.7, 1.0);
        }
};

#endif