#pragma once

#include "shape.h"

class RegularPoly :	public shape
{
private:
	Point Corner1;
	Point Corner2;
public:
	Rect(Point, Point, GfxInfo shapeGfxInfo);
	virtual ~Rect();
	virtual void Draw(GUI* pUI) const;

};

