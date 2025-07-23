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
bool Square::isInside(int x, int y) const
{
	// Check if the point (x,y) is inside the square
	int side = abs(Corner2.x - Corner1.x); // Assuming square is axis-aligned
	return (x >= Corner1.x && x <= Corner1.x + side && y >= Corner1.y && y <= Corner1.y + side);
}
string Square::GetShapeType() const
{
	return "Square";
}