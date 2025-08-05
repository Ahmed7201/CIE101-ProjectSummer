#pragma once
#include "Shapes/Shape.h"

class RegularPoly : public shape
{
private:
    Point Center;       // Center of the regular polygon
    Point Vertex;       // One vertex to determine the radius
    int NumSides;       // Number of sides of the polygon
    double Radius;      // Radius (distance from center to vertex)

public:
    RegularPoly(Point C, Point V, int Sides, GfxInfo shapeGfxInfo);
    virtual ~RegularPoly();
    virtual void Draw(GUI* pUI) const;
    virtual bool isInside(int x, int y) const override;
    virtual string GetShapeType() const override;
    virtual void Rotate(double degrees) override;
    virtual shape* Clone() override;
    virtual void Move(int dx, int dy) override;
    virtual void Scale(double factor) override; // Scale the regular polygon by factor
    virtual void Save(ofstream& OutFile) override;
    virtual void Load(ifstream& Infile) override;
    virtual Point Getcenter() const override;
};