#pragma once
#include "shape.h"

class GroupShape : public shape
{
private:
	shape* shapes[10];  // Array to hold up to 10 shapes
	int numShapes;      // Number of shapes in the group

public:
	GroupShape(shape** shapeArray, int count, GfxInfo shapeGfxInfo);
	virtual ~GroupShape();

	// Override group-related methods
	virtual bool IsGroup() const override { return true; }
	int GetNumShapes() const { return numShapes; }
	shape* GetShape(int index) const;  // Get shape at specific index

	// Override required shape methods
	virtual bool isInside(int x, int y) const override;
	virtual string GetShapeType() const override { return "Group"; }
	virtual Point Getcenter() const override;
	virtual void Draw(GUI* pUI) const override;
	
	// Required virtual methods from base class
	virtual shape* Clone() override;
	virtual void Move(int dx, int dy) override;
	virtual void Rotate(double degrees) override;
	virtual void Scale(double factor) override;
	virtual void Save(ofstream& OutFile) override;
	virtual void Load(ifstream& Infile) override;
}; 