#include "Oval.h"
#include<fstream>

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
	double Distance = sqrt(pow(x - Center.x, 2) + pow(y - Center.y, 2));
	return Distance <= Radius_Oval;
}
string Oval::GetShapeType() const
{
	return "Oval";
}
void Oval::Rotate(double degrees)
{
	// Use a constant for pi since M_PI might not be defined
	const double PI = 3.14159265358979323846;
	// Convert degrees to radians
	double radians = degrees * PI / 180.0;

	// Calculate the initial angle of Edge_Point relative to Center
	double dx = Edge_Point.x - Center.x;
	double dy = Edge_Point.y - Center.y;
	double currentAngle = atan2(dy, dx);

	// Calculate the new angle (add the rotation angle)
	double newAngle = currentAngle + radians;

	// Update Edge_Point with the new position based on Radius_Oval
	Edge_Point.x = Center.x + Radius_Oval * cos(newAngle);
	Edge_Point.y = Center.y + Radius_Oval * sin(newAngle);
}
shape* Oval::Clone()
{
	// Cloning is not implemented for Oval
	return new Oval(*this);
}
void Oval::Move(int dx, int dy)
{
	// Move the oval by dx, dy
	Center.x += dx;
	Center.y += dy;
	Edge_Point.x += dx;
	Edge_Point.y += dy;
}
void Oval::Save(ofstream& OutFile)
{
	// Save the oval parameters to the file
	OutFile << Center.x << " " << Center.y << " " << Edge_Point.x << " " << Edge_Point.y << endl;
	OutFile << (int) ShpGfxInfo.DrawClr.ucRed << " " << (int) ShpGfxInfo.DrawClr.ucGreen << " " << (int) ShpGfxInfo.DrawClr.ucBlue << endl;
	OutFile << (int) ShpGfxInfo.FillClr.ucRed << " " << (int) ShpGfxInfo.FillClr.ucGreen << " " << (int) ShpGfxInfo.FillClr.ucBlue << endl;
	OutFile << ShpGfxInfo.isFilled << endl;
	OutFile << Radius_Oval << endl; // Save the radius of the oval
}
void Oval::Load(ifstream& Infile)
{
	// Load the oval parameters from the file
	Infile >> Center.x >> Center.y >> Edge_Point.x >> Edge_Point.y;
	
	// Explicit casting from int to unsigned char
	int r, g, b;

	// Draw Color
	Infile >> r >> g >> b;
	ShpGfxInfo.DrawClr.ucRed = static_cast<unsigned char>(r);
	ShpGfxInfo.DrawClr.ucGreen = static_cast<unsigned char>(g);
	ShpGfxInfo.DrawClr.ucBlue = static_cast<unsigned char>(b);

	// Fill Color
	Infile >> r >> g >> b;
	ShpGfxInfo.FillClr.ucRed = static_cast<unsigned char>(r);
	ShpGfxInfo.FillClr.ucGreen = static_cast<unsigned char>(g);
	ShpGfxInfo.FillClr.ucBlue = static_cast<unsigned char>(b);

	// Fill flag
	Infile >> ShpGfxInfo.isFilled;

	// Load the radius of the oval
	Infile >> Radius_Oval;
}
Point Oval::Getcenter() const
{
	// Calculate the center point of the oval
	return Center; // The center is already stored in the Center member variable
}


