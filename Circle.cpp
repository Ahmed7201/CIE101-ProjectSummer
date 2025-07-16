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