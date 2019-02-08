#include "nearest_neighbor_brute_force.h"
#include <limits>// std::numeric_limits<double>::infinity();

void nearest_neighbor_brute_force(
        const Eigen::MatrixXd &points,
        const Eigen::RowVector3d &query,
        int &I,
        double &sqrD) {
    ////////////////////////////////////////////////////////////////////////////



    sqrD = std::numeric_limits<double>::infinity();

    double temp_distance;

    for (int i = 0; i < points.rows(); i++) {

        Eigen::RowVector3d d = query - points.row(i);
        temp_distance = pow(d(0), 2) + pow(d(1), 2) + pow(d(2), 2);

        if (temp_distance < sqrD) {
            sqrD = temp_distance;
            I = i;
        }
    }

    ////////////////////////////////////////////////////////////////////////////
}
