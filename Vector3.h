//
// Created by iunits on 25.10.2026.
//

#ifndef LABS_VECTOR3_H
#define LABS_VECTOR3_H


class Vector3 {
public:

    Vector3 (double x1 = 0, double y1 = 0, double z1 = 0,
            double x2 = 0, double y2 = 0, double z2 = 0);

    double getBeginX() const;
    double getBeginY() const;
    double getBeginZ() const;
    double getEndX() const;
    double getEndY() const;
    double getEndZ() const;

    double dx() const;
    double dy() const;
    double dz() const;

    double getdx() const;
    double getdy() const;
    double getdz() const;

    double length() const;

private:
    double x1_, y1_, z1_;
    double x2_, y2_, z2_;
};


#endif //LABS_VECTOR3_H
