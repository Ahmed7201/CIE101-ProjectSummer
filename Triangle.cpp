#include "Triangle.h"
#include <fstream>

Triangle::Triangle(Point P1, Point P2, Point P3, GfxInfo shapeGfxInfo) : shape(shapeGfxInfo)
{
	Corner1 = P1;
	Corner2 = P2;
	Corner3 = P3;
}

Triangle::~Triangle()
{
}

void Triangle::Draw(GUI* pUI) const
{
	//Call Output::DrawTriangle to draw a Triangleangle on the screen
	pUI->DrawTriangle(Corner1, Corner2, Corner3, ShpGfxInfo);
}
bool Triangle::isInside(int x, int y) const
{
	// Check if the point (x,y) is inside the triangle using barycentric coordinates
	double area = 0.5 * (-Corner2.y * Corner3.x + Corner1.y * (-Corner2.x + Corner3.x) + Corner1.x * (Corner2.y - Corner3.y) + Corner2.x * Corner3.y);
	if (area == 0)
	{
		return false; 
	}
	else
	{
		double s = 1 / (2 * area) * (Corner1.y * Corner3.x - Corner1.x * Corner3.y + (Corner3.y - Corner1.y) * x + (Corner1.x - Corner3.x) * y);
		double t = 1 / (2 * area) * (Corner1.x * Corner2.y - Corner1.y * Corner2.x + (Corner1.y - Corner2.y) * x + (Corner2.x - Corner1.x) * y);
		return s >= 0 && t >= 0 && (s + t <= 1);
	}
	
}
string Triangle::GetShapeType() const
{
	return "Triangle"; // Return the shape type
}
void Triangle::Rotate(double degrees)
{
	// Use a constant for pi since M_PI might not be defined
	const double PI = 3.14159265358979323846;
	// Convert degrees to radians
	double radians = degrees * PI / 180.0;

	// Calculate the centroid (center of rotation)
	double centerX = (Corner1.x + Corner2.x + Corner3.x) / 3.0;
	double centerY = (Corner1.y + Corner2.y + Corner3.y) / 3.0;

	// Rotate each corner around the centroid
	// Corner1
	double x = Corner1.x - centerX;
	double y = Corner1.y - centerY;
	Corner1.x = centerX + (x * cos(radians) - y * sin(radians));
	Corner1.y = centerY + (x * sin(radians) + y * cos(radians));

	// Corner2
	x = Corner2.x - centerX;
	y = Corner2.y - centerY;
	Corner2.x = centerX + (x * cos(radians) - y * sin(radians));
	Corner2.y = centerY + (x * sin(radians) + y * cos(radians));

	// Corner3
	x = Corner3.x - centerX;
	y = Corner3.y - centerY;
	Corner3.x = centerX + (x * cos(radians) - y * sin(radians));
	Corner3.y = centerY + (x * sin(radians) + y * cos(radians));
}
shape* Triangle::Clone()
{
	// Cloning is not implemented for Triangle
	return new Triangle(*this);
}
void Triangle::Move(int dx, int dy)
{
	// Move the triangle by dx, dy
	Corner1.x += dx;
	Corner1.y += dy;
	Corner2.x += dx;
	Corner2.y += dy;
	Corner3.x += dx;
	Corner3.y += dy;
}
void Triangle::Save(ofstream& OutFile)
{
	
	OutFile << Corner1.x << " " << Corner1.y << " "
		<< Corner2.x << " " << Corner2.y << " "
		<< Corner3.x << " " << Corner3.y << endl;

	OutFile << (int)ShpGfxInfo.DrawClr.ucRed << " "
		<< (int)ShpGfxInfo.DrawClr.ucGreen << " "
		<< (int)ShpGfxInfo.DrawClr.ucBlue << endl;

	OutFile << (int)ShpGfxInfo.FillClr.ucRed << " "
		<< (int)ShpGfxInfo.FillClr.ucGreen << " "
		<< (int)ShpGfxInfo.FillClr.ucBlue << endl;

	OutFile << ShpGfxInfo.isFilled << endl;
}

	void Triangle::Load(ifstream & Infile)
	{
		// Load the triangle corner points
		Infile >> Corner1.x >> Corner1.y >> Corner2.x >> Corner2.y >> Corner3.x >> Corner3.y;

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

Point Triangle::Getcenter() const
{
	// Calculate the centroid of the triangle
	int centerX = (Corner1.x + Corner2.x + Corner3.x) / 3;
	int centerY = (Corner1.y + Corner2.y + Corner3.y) / 3;
	return Point{ centerX, centerY };
}
