#include "Square.h"
#include<fstream>

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
void Square::Rotate(double degrees)
{}
void Square::Load(ifstream& Infile)
{
	// Load the square parameters from the file
	Infile >> Corner1.x >> Corner1.y >> Corner2.x >> Corner2.y;
	Infile >> ShpGfxInfo.DrawClr.ucRed >> ShpGfxInfo.DrawClr.ucGreen >> ShpGfxInfo.DrawClr.ucBlue;
	Infile >> ShpGfxInfo.FillClr.ucRed >> ShpGfxInfo.FillClr.ucGreen >> ShpGfxInfo.FillClr.ucBlue;
	Infile >> ShpGfxInfo.isFilled;
}