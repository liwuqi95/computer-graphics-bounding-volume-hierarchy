#include "ray_intersect_triangle.h"

bool ray_intersect_triangle(
  const Ray & ray,
  const Eigen::RowVector3d & A,
  const Eigen::RowVector3d & B,
  const Eigen::RowVector3d & C,
  const double min_t,
  const double max_t,
  double & t)
{
  ////////////////////////////////////////////////////////////////////////////

  Eigen::RowVector3d t1 = B - A;
  Eigen::RowVector3d t2 = C - A;

  Eigen::RowVector3d v = ray.direction;
  Eigen::RowVector3d u = A - ray.origin;



  double a = t1(0), b = t2(0), c = -v(0), d = u(0);
  double l = t1(1), m = t2(1), o = -v(1), k = u(1);
  double p = t1(2), q = t2(2), r = -v(2), s = u(2);


  double D = (a*m*r+b*p*o+c*l*q)-(a*o*q+b*l*r+c*m*p);

  t = ((a*q*k+b*l*s+d*m*p)-(a*m*s+b*p*k+d*l*q))/D;

  if (t >= min_t && t <= max_t){

    double alpha = ((b*r*k+c*m*s+d*o*q)-(b*o*s+c*q*k+d*m*r))/D;
    double beta  = ((a*o*s+c*p*k+d*l*r)-(a*r*k+c*l*s+d*o*p))/D;

    if (alpha >= 0 && beta >= 0 && (alpha + beta) <= 1) {
      return true;
    }

  }

  return false;


  ////////////////////////////////////////////////////////////////////////////
}

