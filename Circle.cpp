#include "Circle.h"
#include <fstream>
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
void Circle::Rotate(double degrees)
{}
shape* Circle::Clone()
{
	// Cloning is not implemented for Circle
	return new Circle(*this);
}
void Circle::Move(int dx, int dy)
{
	// Move the circle by dx, dy
	Center.x += dx;
	Center.y += dy;
	Edge_Point.x += dx;
	Edge_Point.y += dy;
	// Update the radius based on the new edge point
	Radius = sqrt(pow(Center.x - Edge_Point.x, 2) + pow(Center.y - Edge_Point.y, 2));
}
void Circle::Save(ofstream& OutFile)
{
	// Save the circle parameters to the file
	OutFile << Center.x << " " << Center.y << " " << Edge_Point.x << " " << Edge_Point.y << endl;
	OutFile << ShpGfxInfo.DrawClr.ucRed << " " << ShpGfxInfo.DrawClr.ucGreen << " " << ShpGfxInfo.DrawClr.ucBlue << endl;
	OutFile << ShpGfxInfo.FillClr.ucRed << " " << ShpGfxInfo.FillClr.ucGreen << " " << ShpGfxInfo.FillClr.ucBlue << endl;
	OutFile << ShpGfxInfo.isFilled << endl;
	OutFile << Radius << endl; // Save the radius of the circle
}

void Circle::Load(ifstream& Infile)
{
	// Load the circle parameters from the file
	Infile >> Center.x >> Center.y >> Edge_Point.x >> Edge_Point.y;
	Infile >> ShpGfxInfo.DrawClr.ucRed >> ShpGfxInfo.DrawClr.ucGreen >> ShpGfxInfo.DrawClr.ucBlue;
	Infile >> ShpGfxInfo.FillClr.ucRed >> ShpGfxInfo.FillClr.ucGreen >> ShpGfxInfo.FillClr.ucBlue;
	Infile >> ShpGfxInfo.isFilled;
	Radius = sqrt(pow(Center.x - Edge_Point.x, 2) + pow(Center.y - Edge_Point.y, 2));
}
Point Circle::Getcenter() const
{
	// Calculate the center point of the circle
	return Center;
}
