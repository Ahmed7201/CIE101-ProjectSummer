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
	virtual shape* Clone() override; // Cloning is not implemented for Line
	virtual void Move(int dx, int dy) override; // Move the line by dx, dy
	virtual void Save(ofstream& OutFile) override; // Save the line parameters to a file
	virtual void Load(ifstream& Infile) override; // Load the line parameters from a file
	virtual Point Getcenter() const override; // Get the center point of the line


};


