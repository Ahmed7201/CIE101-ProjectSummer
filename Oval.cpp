#include "Oval.h"

Oval::Oval(Point P1, Point P2, GfxInfo shapeGfxInfo) :shape(shapeGfxInfo)
{
	Center = P1;
	Edge_Point = P2;
	Radius_Oval= sqrt(pow(Center.x - Edge_Point.x, 2) + pow(Center.y - Edge_Point.y, 2)) ; 
}
Oval::~Oval()
{ }
void Oval::Draw(GUI* pUI) const
{
	pUI->DrawOval(Center, Edge_Point, ShpGfxInfo);
}
bool Oval::isInside(int x, int y) const
{
	double distance = sqrt(pow(x - Center.x, 2) + pow(y - Center.y, 2));
	return distance <= Radius_Oval;
}
string Oval::GetShapeType() const
{
	return "Oval";
}