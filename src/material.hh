#ifndef MATERIAL_H
#define MATERIAL_H

#include "hittable.hh"

class Material {
    public: 
        virtual ~Material() = default;

        virtual bool scatter(const Ray& r, const Hit_Record& rec,
            Color& attenuation, Ray& scattered) const {
                return false;       
            }
};

#endif