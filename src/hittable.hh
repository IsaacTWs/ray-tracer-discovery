#ifndef HITTABLE_H
#define HITTABLE_H

#include "commons.hh"

class Material;

class Hit_Record {
    public:
        Point3 p;
        Vec3 normal;
        double t;
        bool front_face;
        shared_ptr<Material> mat;

        void set_face_normal(const Ray& r, const Vec3& outward_normal) {
            //sets hit record normal vector - assumes arg[1] to have unit length
            front_face = dot(r.direction(), outward_normal) < 0;
            normal = front_face ? outward_normal : -outward_normal;
        }
};

class Hittable {
    public:
        virtual ~Hittable() = default;
        virtual bool hit(const Ray& r, Interval ray_t, Hit_Record& rec) const = 0;
};

#endif