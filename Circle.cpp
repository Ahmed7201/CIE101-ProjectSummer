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
	// Check if the shape has an image attached
	if (HasImage()) {
		// Create a temporary graphics info without fill for the border
		GfxInfo borderInfo = ShpGfxInfo;
		borderInfo.isFilled = false; // Don't fill when we have an image
		
		// Draw the shape border first
		pUI->DrawCircle(Center, Radius, borderInfo);
		
		// Calculate the circle bounds
		int x = Center.x - Radius;
		int y = Center.y - Radius;
		int width = 2 * Radius;
		int height = 2 * Radius;
		
		// Draw the image inside the shape (this will be drawn on top of the border)
		pUI->DrawImage_InsideShape(GetImagePath(), x, y, width, height);
	} else {
		// Draw the shape normally with fill
		pUI->DrawCircle(Center, Radius, ShpGfxInfo);
	}
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
shape* Circle::Clone()  {
	return new Circle(*this); // Uses the copy constructor
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



void Circle::Scale(double factor)
{
	// Scale the radius
	Radius *= factor;
	
	// Update the edge point to maintain the same direction from center
	double dx = Edge_Point.x - Center.x;
	double dy = Edge_Point.y - Center.y;
	double distance = sqrt(dx * dx + dy * dy);
	
	if (distance > 0) {
		// Normalize and scale
		dx = (dx / distance) * Radius;
		dy = (dy / distance) * Radius;
		Edge_Point.x = Center.x + dx;
		Edge_Point.y = Center.y + dy;
	}
}
void Circle::Save(ofstream& OutFile)
{
	// Save the circle parameters to the file
	OutFile << Center.x << " " << Center.y << " " << Edge_Point.x << " " << Edge_Point.y << endl;
	OutFile << (int) ShpGfxInfo.DrawClr.ucRed << " " << (int) ShpGfxInfo.DrawClr.ucGreen << " " << (int) ShpGfxInfo.DrawClr.ucBlue << endl;
	OutFile << (int) ShpGfxInfo.FillClr.ucRed << " " << (int) ShpGfxInfo.FillClr.ucGreen << " " << (int) ShpGfxInfo.FillClr.ucBlue << endl;
	OutFile << ShpGfxInfo.isFilled << endl;
	OutFile << Radius << endl; // Save the radius of the circle
}

void Circle::Load(ifstream& Infile)
{
	// Load the circle parameters from the file
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

	// Load the radius of the circle
	Infile >> Radius;
}
Point Circle::Getcenter() const
{
	// Calculate the center point of the circle
	return Center;
}
