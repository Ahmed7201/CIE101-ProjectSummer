#pragma once

#include "Shapes/shape.h"

class Line : public shape
{
private:
	Point point1;
	Point point2;
public:
	Line(Point, Point, GfxInfo shapeGfxInfo);
	virtual ~Line();
	virtual void Draw(GUI* pUI) const;
};


