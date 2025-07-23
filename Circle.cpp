#include "Circle.h"
Circle::Circle(Point P1,Point P2, GfxInfo shapeGfxInfo) : shape(shapeGfxInfo)
{
	
	Center = P1;
	Edge_Point = P2; // Point on the circumference of the circle
	Radius =sqrt(pow(Center.x - Edge_Point.x, 2) + pow(Center.y - Edge_Point.y, 2)); ; // Default radius
}
Circle::~Circle()
{}

void Circle::Draw(GUI* pUI) const
{
	// Call Output::DrawCircle to draw a circle on the screen
	pUI->DrawCircle(Center, Radius, ShpGfxInfo);
}
void Circle::SetRadius(int r)
{
	Radius = r;
}
double Circle::GetRadius() const
{
	return Radius;
}
Point Circle::GetCenter() const
{
	return Center;
}
bool Circle::isInside(int x, int y) const
{
	// Check if the point (x,y) is inside the circle using the distance formula
	double distance = sqrt(pow(x - Center.x, 2) + pow(y - Center.y, 2));
	return distance <= Radius;
}
string Circle::GetShapeType() const
{
	return "Circle"; // Return the shape type
}
