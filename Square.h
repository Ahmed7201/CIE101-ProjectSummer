#pragma once

#include "Shapes/shape.h"

class Square : public shape
{
private:
	Point Corner1;
	Point Corner2;
public:
	Square(Point, Point, GfxInfo shapeGfxInfo);
	virtual ~Square();
	virtual void Draw(GUI* pUI) const;
	virtual bool isInside(int x, int y) const override;
	virtual string GetShapeType() const override; // Added to get the shape type
	virtual void Rotate(double degrees) override; // Rotate the square by a given angle
	virtual void Save(ofstream& OutFile) override; // Save the square parameters to a file
	virtual void Load(ifstream& Infile) override; // Load the square parameters from a file

};

