#include "Rect.h"

Rect::Rect(Point P1, Point P2, GfxInfo shapeGfxInfo):shape(shapeGfxInfo)
{
	Corner1 = P1;
	Corner2 = P2;
}

Rect::~Rect()
{}



void Rect::Draw(GUI* pUI) const
{
	//Call Output::DrawRect to draw a rectangle on the screen	
	
	pUI->DrawRect(Corner1, Corner2, ShpGfxInfo);

}
bool Rect::isInside(int x, int y) const
{
	//Check if the point (x,y) is inside the rectangle
	return (x >= Corner1.x && x <= Corner2.x && y >= Corner1.y && y <= Corner2.y);
}
string Rect::GetShapeType() const
{
	return "Rectangle"; // Return the shape type
}