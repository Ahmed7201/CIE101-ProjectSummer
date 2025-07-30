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
	virtual bool isInside(int x, int y) const override;
	virtual string GetShapeType() const override; // Return the shape type
	virtual void Rotate(double degrees) override; // Rotate the line by a given angle
};


