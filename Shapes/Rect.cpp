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
	// Check if the shape has an image attached
	if (HasImage()) {
		// Create a temporary graphics info without fill for the border
		GfxInfo borderInfo = ShpGfxInfo;
		borderInfo.isFilled = false; // Don't fill when we have an image
		
		// Draw the shape border first
		pUI->DrawRect(Corner1, Corner2, borderInfo);
		
		// Calculate the rectangle bounds
		int x = min(Corner1.x, Corner2.x);
		int y = min(Corner1.y, Corner2.y);
		int width = abs(Corner2.x - Corner1.x);
		int height = abs(Corner2.y - Corner1.y);
		
		// Draw the image inside the shape (this will be drawn on top of the border)
		pUI->DrawImage_InsideShape(GetImagePath(), x, y, width, height);
	} else {
		// Draw the shape normally with fill
	pUI->DrawRect(Corner1, Corner2, ShpGfxInfo);
	}
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

void Rect::Scale(double factor)
{
	// Calculate the center of the rectangle
	double centerX = (Corner1.x + Corner2.x) / 2.0;
	double centerY = (Corner1.y + Corner2.y) / 2.0;

	// Calculate the current width and height
	double width = abs(Corner2.x - Corner1.x);
	double height = abs(Corner2.y - Corner1.y);

	// Calculate new width and height
	double newWidth = width * factor;
	double newHeight = height * factor;

	// Calculate new corners relative to center
	double halfWidth = newWidth / 2.0;
	double halfHeight = newHeight / 2.0;

	// Update corners
	Corner1.x = centerX - halfWidth;
	Corner1.y = centerY - halfHeight;
	Corner2.x = centerX + halfWidth;
	Corner2.y = centerY + halfHeight;
}

void Rect::Save(ofstream& OutFile) 
{
	// Save the rectangle parameters to the file
	OutFile << Corner1.x << " " << Corner1.y << " " << Corner2.x << " " << Corner2.y << endl;
	OutFile << (int) ShpGfxInfo.DrawClr.ucRed << " " << (int) ShpGfxInfo.DrawClr.ucGreen << " " << (int) ShpGfxInfo.DrawClr.ucBlue << endl;
	OutFile << (int) ShpGfxInfo.FillClr.ucRed << " " << (int)ShpGfxInfo.FillClr.ucGreen << " " << (int)ShpGfxInfo.FillClr.ucBlue << endl;
	OutFile << ShpGfxInfo.isFilled << endl;
}
void Rect::Load(ifstream& Infile)
{
	// Load the rectangle parameters from the file
	Infile >> Corner1.x >> Corner1.y >> Corner2.x >> Corner2.y;

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
}
Point Rect::Getcenter() const
{
	// Get the center point of the rectangle
	Point center;
	center.x = (Corner1.x + Corner2.x) / 2;
	center.y = (Corner1.y + Corner2.y) / 2;
	return center;
}


	
