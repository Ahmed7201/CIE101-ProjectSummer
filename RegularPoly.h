#pragma once
#include "Shapes/Shape.h"

class RegularPoly : public shape {
private:
    Point Center;           // Center of the polygon
    int numSides;           // Number of sides
    double Radius;          // Distance from center to vertices
    double initialAngle;    // Angle of the first point
    Point Edge_Point; //Point on the shape
public:
    RegularPoly(Point Center, Point Edge_Point, int sides, GfxInfo shapeGfx);

    virtual void Draw(GUI* pUI) const override; // Draw the shape
};
