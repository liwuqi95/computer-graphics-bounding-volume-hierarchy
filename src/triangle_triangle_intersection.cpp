#include "triangle_triangle_intersection.h"
#include "ray_intersect_triangle.h"

bool triangle_triangle_intersection(
        const Eigen::RowVector3d &A0,
        const Eigen::RowVector3d &A1,
        const Eigen::RowVector3d &A2,
        const Eigen::RowVector3d &B0,
        const Eigen::RowVector3d &B1,
        const Eigen::RowVector3d &B2) {
    ////////////////////////////////////////////////////////////////////////////

    bool intersect = false;

    double t;

    if (!intersect) {
        Ray ray1 = Ray(Eigen::Vector3d(A0(0), A0(1), A0(2)),
                       Eigen::Vector3d(A1(0) - A0(0), A1(1) - A0(1), A1(2) - A0(2)));
        intersect = ray_intersect_triangle(ray1, B0, B1, B2, 0, 1, t);
    }

    if (!intersect) {
        Ray ray2 = Ray(Eigen::Vector3d(A0(0), A0(1), A0(2)),
                       Eigen::Vector3d(A2(0) - A0(0), A2(1) - A0(1), A2(2) - A0(2)));
        intersect = ray_intersect_triangle(ray2, B0, B1, B2, 0, 1, t);
    }

    if (!intersect) {
        Ray ray3 = Ray(Eigen::Vector3d(A1(0), A1(1), A1(2)),
                       Eigen::Vector3d(A2(0) - A1(0), A2(1) - A1(1), A2(2) - A1(2)));
        intersect = ray_intersect_triangle(ray3, B0, B1, B2, 0, 1, t);
    }

    return intersect;

    ////////////////////////////////////////////////////////////////////////////
}
