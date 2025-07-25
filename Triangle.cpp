#include "Triangle.h"

Triangle::Triangle(Point P1, Point P2, Point P3, GfxInfo shapeGfxInfo) : shape(shapeGfxInfo)
{
	Corner1 = P1;
	Corner2 = P2;
	Corner3 = P3;
}

Triangle::~Triangle()
{
}

void Triangle::Draw(GUI* pUI) const
{
	//Call Output::DrawTriangle to draw a Triangleangle on the screen
	pUI->DrawTriangle(Corner1, Corner2, Corner3, ShpGfxInfo);
}
bool Triangle::isInside(int x, int y) const
{
	// Check if the point (x,y) is inside the triangle using barycentric coordinates
	double area = 0.5 * (-Corner2.y * Corner3.x + Corner1.y * (-Corner2.x + Corner3.x) + Corner1.x * (Corner2.y - Corner3.y) + Corner2.x * Corner3.y);
	if (area == 0)
	{
		return false; 
	}
	else
	{
		double s = 1 / (2 * area) * (Corner1.y * Corner3.x - Corner1.x * Corner3.y + (Corner3.y - Corner1.y) * x + (Corner1.x - Corner3.x) * y);
		double t = 1 / (2 * area) * (Corner1.x * Corner2.y - Corner1.y * Corner2.x + (Corner1.y - Corner2.y) * x + (Corner2.x - Corner1.x) * y);
		return s >= 0 && t >= 0 && (s + t <= 1);
	}
	
}
string Triangle::GetShapeType() const
{
	return "Triangle"; // Return the shape type
}

