#include "ray_intersect_box.h"
#include <iostream>

bool ray_intersect_box(
        const Ray &ray,
        const BoundingBox &box,
        const double min_t,
        const double max_t) {
    ////////////////////////////////////////////////////////////////////////////


    double tx_min = ((ray.direction(0) >= 0 ? box.min_corner(0) : box.max_corner(0)) - ray.origin(0)) / ray.direction(0);
    double tx_max = ((ray.direction(0) >= 0 ? box.max_corner(0) : box.min_corner(0)) - ray.origin(0)) / ray.direction(0);

    double ty_min = ((ray.direction(1) >= 0 ? box.min_corner(1) : box.max_corner(1)) - ray.origin(1)) / ray.direction(1);
    double ty_max = ((ray.direction(1) >= 0 ? box.max_corner(1) : box.min_corner(1)) - ray.origin(1)) / ray.direction(1);

    double tz_min = ((ray.direction(2) >= 0 ? box.min_corner(2) : box.max_corner(2)) - ray.origin(2)) / ray.direction(2);
    double tz_max = ((ray.direction(2) >= 0 ? box.max_corner(2) : box.min_corner(2)) - ray.origin(2)) / ray.direction(2);



    double min = fmin(fmin(tx_max,ty_max),tz_max);
    double max = fmax(fmax(tx_min,ty_min),tz_min);




    return (min <= max) && (min >= min_t) && (max <= max_t);
    ////////////////////////////////////////////////////////////////////////////
}
