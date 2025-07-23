#include "Line.h"

Line::Line(Point P1, Point P2, GfxInfo shapeGfxInfo) :shape(shapeGfxInfo)
{
	point1 = P1;
	point2 = P2;
}

Line::~Line()
{
}

void Line::Draw(GUI* pUI) const
{
	//Call Output::DrawSquare to draw a Line on the screen	
	pUI->DrawLine(point1, point2, ShpGfxInfo);
}
bool Line::isInside(int x, int y) const
{
	// Check if the point (x,y) is on the line segment defined by point1 and point2
	double crossProduct = (y - point1.y) * (point2.x - point1.x) - (x - point1.x) * (point2.y - point1.y);
	if (abs(crossProduct) > 1e-6) // Check if the point is not on the line
		return false;
	double dotProduct = (x - point1.x) * (point2.x - point1.x) + (y - point1.y) * (point2.y - point1.y);
	if (dotProduct < 0)
		return false;
	double squaredLength = pow(point2.x - point1.x, 2) + pow(point2.y - point1.y, 2);
	if (dotProduct > squaredLength)
		return false;
	return true; // The point is on the line segment
}
string Line::GetShapeType() const
{
	return "Line"; // Return the shape type as a string
}