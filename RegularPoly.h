#pragma once

#include "Shapes/shape.h"

class RegularPoly :	public shape
{
private:
	Point Corner1;
	Point Corner2;
public:
	RegularPoly(Point P1, Point, GfxInfo shapeGfxInfo);
	virtual ~RegularPoly();
	virtual void Draw(GUI* pUI) const;

};

