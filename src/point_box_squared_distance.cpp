#include "point_box_squared_distance.h"

double point_box_squared_distance(
        const Eigen::RowVector3d &query,
        const BoundingBox &box) {
    ////////////////////////////////////////////////////////////////////////////


    double distance = 0;
    for (int i = 0; i < 3; i++) {
        distance += fmin(pow(query(0) - box.max_corner(0), 2), pow(query(0) - box.min_corner(0), 2));
    }

    return distance;

    ////////////////////////////////////////////////////////////////////////////
}
