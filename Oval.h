#pragma once
#include "Shapes/Shape.h"
class Oval :
    public shape
{
private:
    Point Center, Edge_Point;
    double Radius_Oval;
public:
    Oval(Point P1, Point P2, GfxInfo shapeGfxInfo);
    virtual ~Oval();
    virtual void Draw(GUI* pUI) const;
    virtual bool isInside(int x, int y) const override;
    virtual string GetShapeType() const override;
	virtual void Rotate( double degrees) override; // Rotate the oval by a given angle
	virtual void Load(ifstream& Infile) override; // Load the oval parameters from a file

};

