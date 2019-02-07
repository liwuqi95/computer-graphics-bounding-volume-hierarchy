#include "ray_intersect_box.h"
#include <iostream>

bool ray_intersect_box(
        const Ray &ray,
        const BoundingBox &box,
        const double min_t,
        const double max_t) {
    ////////////////////////////////////////////////////////////////////////////

    double max_l, min_l;
    double temp_min, temp_max;

    for (int i = 0; i < 3; i++) {

        if (ray.direction(i) >= 0) {
            temp_min = box.min_corner(i) - ray.origin(i);
            temp_max = box.max_corner(i) - ray.origin(i);
        } else {
            temp_min = box.max_corner(i) - ray.origin(i);
            temp_max = box.min_corner(i) - ray.origin(i);
        }

        temp_min /= ray.direction(i);
        temp_max /= ray.direction(i);



        if (i == 0 || temp_min > min_l)
            min_l = temp_min;
        if (i == 0 || temp_max < max_l)
            max_l = temp_max;
    }


    return (max_l >= min_l) && (fmin(max_t, max_l) >= fmax(min_t, min_l));

    ////////////////////////////////////////////////////////////////////////////
}
