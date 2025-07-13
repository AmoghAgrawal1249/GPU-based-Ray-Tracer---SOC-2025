#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"

class sphere : public hittable {
  public:
    sphere(const point3& sphere_center, double sphere_radius) : center(sphere_center), radius(std::fmax(0, sphere_radius)) {}

    bool hit(const ray& input_ray, interval ray_t, hit_record& record) const override {
        vec3 oc = center - input_ray.getOrigin();
        auto a = input_ray.getDirection().getDotProduct(input_ray.getDirection());
        auto h = input_ray.getDirection().getDotProduct(oc);
        auto c = oc.getDotProduct(oc) - radius * radius;

        auto discriminant = h * h - a * c;
        if (discriminant < 0)
            return false;

        auto sqrtd = std::sqrt(discriminant);

        // Find the nearest root that lies in the acceptable range.
        auto root = (h - sqrtd) / a;
        if (!ray_t.surrounds(root)) {
            root = (h + sqrtd) / a;
            if (!ray_t.surrounds(root))
                return false;
        }

        record.hit_t = root;
        record.hit_point = input_ray.getPointAtDistance(record.hit_t);
        vec3 outward_normal = (record.hit_point - center) / radius;
        record.set_face_normal(input_ray, outward_normal);

        return true;
    }

  private:
    point3 center;
    double radius;
};

#endif