#include "Square.h"

Square::Square(Point P1, Point P2, GfxInfo shapeGfxInfo) :shape(shapeGfxInfo)
{
	Corner1 = P1;
	Corner2 = P2;
	int dx = P2.x - P1.x;
	int dy = P2.y - P1.y;

}

Square::~Square()
{
}

void Square::Draw(GUI* pUI) const
{
	//Call Output::DrawSquare to draw a Square on the screen	
	pUI->DrawSquare(Corner1, Corner2, ShpGfxInfo);
}