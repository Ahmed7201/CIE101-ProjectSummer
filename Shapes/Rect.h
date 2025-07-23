#pragma once

#include "shape.h"

class Rect : public shape
{
private:
	Point Corner1;	
	Point Corner2;
public:
	Rect(Point , Point, GfxInfo shapeGfxInfo );
	virtual ~Rect();
	virtual void Draw(GUI* pUI) const;
	virtual bool isInside(int x, int y) const override;
	virtual string GetShapeType() const override;// Return the shape type
	
};

