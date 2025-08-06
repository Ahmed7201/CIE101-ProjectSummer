#include "GroupShape.h"
using namespace std;

GroupShape::GroupShape(shape** shapeArray, int count, GfxInfo shapeGfxInfo) : shape(shapeGfxInfo)
{
	numShapes = count;
	if (numShapes > 10) numShapes = 10; // Limit to 10 shapes
	
	// Copy shapes to the array
	for (int i = 0; i < numShapes; i++) {
		shapes[i] = shapeArray[i];
	}
}

GroupShape::~GroupShape()
{
	// Clear the shapes array to prevent accessing deleted shapes
	for (int i = 0; i < 10; i++) {
		shapes[i] = nullptr;
	}
	numShapes = 0;
}

shape* GroupShape::GetShape(int index) const
{
	if (index >= 0 && index < numShapes) {
		return shapes[index];
	}
	return nullptr;
}

bool GroupShape::isInside(int x, int y) const
{
	// Check if the point is inside any of the shapes in the group
	for (int i = 0; i < numShapes; i++) {
		if (shapes[i] && shapes[i]->isInside(x, y)) {
			return true;
		}
	}
	return false;
}

Point GroupShape::Getcenter() const
{
	if (numShapes == 0) {
		return Point{0, 0};
	}

	// Calculate the center as the average of all shape centers
	int sumX = 0, sumY = 0;
	for (int i = 0; i < numShapes; i++) {
		if (shapes[i]) {
			Point center = shapes[i]->Getcenter();
			sumX += center.x;
			sumY += center.y;
		}
	}
	
	return Point{sumX / numShapes, sumY / numShapes};
}

void GroupShape::Draw(GUI* pUI) const
{
	// Draw all shapes in the group
	for (int i = 0; i < numShapes; i++) {
		if (shapes[i]) {
			shapes[i]->Draw(pUI);
		}
	}
}

// Required virtual methods from base class - minimal implementations
shape* GroupShape::Clone()
{
	// Empty implementation - not needed
	return nullptr;
}

void GroupShape::Move(int dx, int dy)
{
	// Empty implementation - not needed
}

void GroupShape::Rotate(double degrees)
{
	// Empty implementation - not needed
}

void GroupShape::Scale(double factor)
{
	// Empty implementation - not needed
}

void GroupShape::Save(ofstream& OutFile)
{
	// Empty implementation - not needed
}

void GroupShape::Load(ifstream& Infile)
{
	// Empty implementation - not needed
}

