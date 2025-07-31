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
	virtual void Rotate(double degrees) override; // Rotate the rectangle by a given angle
	virtual shape* Clone() override ; // Cloning is not implemented for Rect
	virtual void Move(int dx, int dy) override; // Move the rectangle by dx, dy
	virtual void Save(ofstream& OutFile) override; // Save the rectangle parameters to a file
	virtual void Load(ifstream& Infile) override; // Load the rectangle parameters from a file
	
};

