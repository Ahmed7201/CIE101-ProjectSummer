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
	virtual shape* Clone() override; // Cloning is not implemented for Square
	virtual void Move(int dx, int dy) override; // Move the square by dx, dy
	virtual void Scale(double factor) override; // Scale the square by factor
	virtual void Save(ofstream& OutFile) override; // Save the square parameters to a file
	virtual void Load(ifstream& Infile) override; // Load the square parameters from a file
	virtual Point Getcenter() const override; // Get the center point of the square
	

};

