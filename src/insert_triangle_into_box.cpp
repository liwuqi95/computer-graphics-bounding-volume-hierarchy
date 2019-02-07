#include "insert_triangle_into_box.h"

void insert_triangle_into_box(
        const Eigen::RowVector3d &a,
        const Eigen::RowVector3d &b,
        const Eigen::RowVector3d &c,
        BoundingBox &B) {
    ////////////////////////////////////////////////////////////////////////////
    B.min_corner(0) = fmin(a(0), fmin(b(0), c(0)));
    B.max_corner(0) = fmax(a(0), fmax(b(0), c(0)));

    B.min_corner(1) = fmin(a(1), fmin(b(1), c(1)));
    B.max_corner(1) = fmax(a(1), fmax(b(1), c(1)));

    B.min_corner(2) = fmin(a(2), fmin(b(2), c(2)));
    B.max_corner(2) = fmax(a(2), fmax(b(2), c(2)));
    ////////////////////////////////////////////////////////////////////////////
}


