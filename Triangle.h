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
	virtual void Rotate(double degrees) override; // Rotate the triangle by a given angle
	virtual shape* Clone() override; // Cloning is not implemented for Triangle
	virtual void Move(int dx, int dy) override; // Move the triangle by dx, dy
	virtual void Scale(double factor) override; // Scale the triangle by factor
	virtual void Save(ofstream& OutFile) override; // Save the triangle parameters to a file
	virtual void Load(ifstream& Infile) override; // Load the triangle parameters from a file
	virtual Point Getcenter() const override; // Get the center point of the triangle


};
