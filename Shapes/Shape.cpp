#include "shape.h"

shape::shape(GfxInfo shapeGfxInfo)
{ 
	ShpGfxInfo = shapeGfxInfo;	//Default status is non-filled.
}
 
void shape::SetSelected(bool s)
{	ShpGfxInfo.isSelected = s; }

double shape::CalcRadius(Point center, Point edge)
{
	double radius = sqrt(pow(center.x - edge.x, 2) + pow(center.y - edge.y, 2));
	return radius;
}

bool shape::IsSelected() const
{	return ShpGfxInfo.isSelected; }

void shape::ChngDrawClr(color Dclr)
{	ShpGfxInfo.DrawClr = Dclr; }

void shape::ChngFillClr(color Fclr)
{	
	ShpGfxInfo.isFilled = true;
	ShpGfxInfo.FillClr = Fclr; 
}
void shape::SetGfxInfo(GfxInfo gfxInfo)
{
	ShpGfxInfo = gfxInfo; // Set the shape's graphical info
} // Set the shape's graphical info
GfxInfo shape::GetGfxInfo()const
{
	return ShpGfxInfo;
} // Return the shape's graphical info

