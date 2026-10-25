//
// Created by iunits on 25.10.2026.
//

#include "Vector3.h"
#include <cmath>

 Vector3 :: Vector3(double x1, double y1, double z1,
     double x2, double y2, double z2)
: x1_(x1),y1_(y1),z1_(z1), x2_(x2),y2_(y2),z2_(z2){}

double Vector3::getBeginX() const {return x1_;}
double Vector3::getBeginY() const {return y1_;}
double Vector3::getBeginZ() const {return z1_;}
double Vector3::getEndX() const {return x2_;}
double Vector3::getEndY() const {return y2_;}
double Vector3::getEndZ() const {return z2_;}

double Vector3::dx() const {return x2_ - x1_;}
double Vector3::dy() const {return y2_ - y1_;}
double Vector3::dz() const {return z2_ - z1_;}

double Vector3::getdx() const {return dx();}
double Vector3::getdy() const {return dy();}
double Vector3::getdz() const {return dz();}


double Vector3::length() const {
  return std::sqrt(dx()*dx()+dy()*dy()+dz()*dz());
 }