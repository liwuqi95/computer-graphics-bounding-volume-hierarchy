#include "point_box_squared_distance.h"

double point_box_squared_distance(
        const Eigen::RowVector3d &query,
        const BoundingBox &box) {
    ////////////////////////////////////////////////////////////////////////////
    double distance = 0, distance_1, distance_2;

    for (int i = 0; i < 3; i++) {

        distance_1 = query(i) - box.min_corner(i);
        distance_2 = query(i) - box.max_corner(i);

        if (distance_1 * distance_2 > 0) {
            distance += fmin(pow(distance_1, 2), pow(distance_2, 2));
        }
    }

    return distance;
    ////////////////////////////////////////////////////////////////////////////
}
