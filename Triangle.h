#pragma once
#include "Shapes/Shape.h"
class Triangle : public shape
{
private:
	Point Corner1;
	Point Corner2;
	Point Corner3;
public:
	Triangle(Point, Point, Point, GfxInfo shapeGfxInfo);
	virtual ~Triangle();
	virtual void Draw(GUI* pUI) const;
	virtual bool isInside(int x, int y) const override;
	virtual string GetShapeType() const override; // Return the shape type
	
};
