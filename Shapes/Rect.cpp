#include "Rect.h"
#include <fstream>

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
void Rect::Rotate(double degrees)
{
	const double M_PI = 3.14159265358979323846; // Define Pi constant
	// Convert degrees to radians
	double radians = degrees *  M_PI / 180.0;

	// Calculate the center of the rectangle
	double centerX = (Corner1.x + Corner2.x) / 2.0;
	double centerY = (Corner1.y + Corner2.y) / 2.0;

	// Rotate each corner around the center
	// TopLeft
	double x = Corner1.x - centerX;
	double y = Corner1.y - centerY;
	Corner1.x = centerX + (x * cos(radians) - y * sin(radians));
	Corner1.y = centerY + (x * sin(radians) + y * cos(radians));

	// BottomRight
	x = Corner2.x - centerX;
	y = Corner2.y - centerY;
	Corner2.x = centerX + (x * cos(radians) - y * sin(radians));
	Corner2.y = centerY + (x * sin(radians) + y * cos(radians));
}
shape* Rect::Clone()
{
	// Cloning is not implemented for Rect
	return new Rect(*this); 
}
void Rect::Move(int dx, int dy)
{
	// Move the rectangle by dx, dy
	Corner1.x += dx;
	Corner1.y += dy;
	Corner2.x += dx;
	Corner2.y += dy;
}

void Rect::Save(ofstream& OutFile) 
{
	// Save the rectangle parameters to the file
	OutFile << Corner1.x << " " << Corner1.y << " " << Corner2.x << " " << Corner2.y << endl;
	OutFile << ShpGfxInfo.DrawClr.ucRed << " " << ShpGfxInfo.DrawClr.ucGreen << " " << ShpGfxInfo.DrawClr.ucBlue << endl;
	OutFile << ShpGfxInfo.FillClr.ucRed << " " << ShpGfxInfo.FillClr.ucGreen << " " << ShpGfxInfo.FillClr.ucBlue << endl;
	OutFile << ShpGfxInfo.isFilled << endl;
}
void Rect::Load(ifstream& Infile)
{
	// Load the rectangle parameters from the file
	Infile >> Corner1.x >> Corner1.y >> Corner2.x >> Corner2.y;
	Infile >> ShpGfxInfo.DrawClr.ucRed >> ShpGfxInfo.DrawClr.ucGreen >> ShpGfxInfo.DrawClr.ucBlue;
	Infile >> ShpGfxInfo.FillClr.ucRed >> ShpGfxInfo.FillClr.ucGreen >> ShpGfxInfo.FillClr.ucBlue;
	Infile >> ShpGfxInfo.isFilled;
}
Point Rect::Getcenter() const
{
	// Get the center point of the rectangle
	Point center;
	center.x = (Corner1.x + Corner2.x) / 2;
	center.y = (Corner1.y + Corner2.y) / 2;
	return center;
}


	
