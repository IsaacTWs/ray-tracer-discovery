#include "commons.hh"
#include "camera.hh"
#include "hittable.hh"
#include "hittable_list.hh"
#include "material.hh"
#include "sphere.hh"

int main() {
    Hittable_List world;

    auto material_ground = make_shared<Lambertian>(Color(0.8, 0.8, 0.0));
    auto material_center = make_shared<Lambertian>(Color(0.1, 0.2, 0.5));
    auto material_left = make_shared<Dielectric>(1.5); //sphere material index of refaction / world index of refraction
    auto material_bubble = make_shared<Dielectric>(1.00 / 1.50);
    auto material_right = make_shared<Metal>(Color(0.8,0.6,0.2), 1.0);

    world.add(make_shared<Sphere>(Point3(0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(make_shared<Sphere>(Point3(0.0, 0.0, -1.2), 0.5, material_center));
    world.add(make_shared<Sphere>(Point3(-1.0,0,-1.0), 0.5, material_left));
    world.add(make_shared<Sphere>(Point3(-1.0, 0, -1.0), 0.4, material_bubble));
    world.add(make_shared<Sphere>(Point3(1.0,0,-1.0), 0.5, material_right));

    Camera cam;

    cam.aspect_ratio = 16.0/9.0;
    cam.image_width = 400;
    cam.samples_per_pixel = 100;
    cam.max_depth = 50;

    cam.render(world);
}