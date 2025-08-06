#include "RegularPoly.h"
#include <fstream>
#include <cmath>

RegularPoly::RegularPoly(Point C, Point V, int Sides, GfxInfo shapeGfxInfo) : shape(shapeGfxInfo)
{
    Center = C;
    Vertex = V;
    NumSides = Sides;
    Radius = sqrt(pow(Center.x - Vertex.x, 2) + pow(Center.y - Vertex.y, 2));
}

RegularPoly::~RegularPoly()
{
}

void RegularPoly::Draw(GUI* pUI) const
{
	// Check if the shape has an image attached
	if (HasImage()) {
		// Create a temporary graphics info without fill for the border
		GfxInfo borderInfo = ShpGfxInfo;
		borderInfo.isFilled = false; // Don't fill when we have an image
		
		// Draw the shape border first
		// Calculate the starting angle based on the Vertex position
		const double PI = 3.14159265358979323846;
		double startAngle = atan2(Vertex.y - Center.y, Vertex.x - Center.x);
		
		// Use the GUI's DrawPolygon method with the calculated starting angle
		pUI->DrawPolygon(Center, Radius, NumSides, borderInfo, startAngle);
		
		// Calculate the polygon bounds
		int x = Center.x - Radius;
		int y = Center.y - Radius;
		int width = 2 * Radius;
		int height = 2 * Radius;
		
		// Draw the image inside the shape (this will be drawn on top of the border)
		pUI->DrawImage_InsideShape(GetImagePath(), x, y, width, height);
	} else {
		// Draw the shape normally with fill
		// Calculate the starting angle based on the Vertex position
		const double PI = 3.14159265358979323846;
		double startAngle = atan2(Vertex.y - Center.y, Vertex.x - Center.x);
		
		// Use the GUI's DrawPolygon method with the calculated starting angle
		pUI->DrawPolygon(Center, Radius, NumSides, ShpGfxInfo, startAngle);
	}
}


bool RegularPoly::isInside(int x, int y) const
{
    // Step 1: Check if the point is within the circumscribed circle for quick rejection
    double distance = sqrt(pow(x - Center.x, 2) + pow(y - Center.y, 2));
    if (distance > Radius) {
        return false; // Point is outside the circumscribed circle
    }

    // Step 2: Use ray-casting algorithm to determine if the point is inside the polygon
    // Calculate the angle between each pair of consecutive vertices
    const double PI = 3.14159265358979323846;
    double angleStep = 2.0 * PI / NumSides;
    double initialAngle = atan2(Vertex.y - Center.y, Vertex.x - Center.x);
    bool inside = false;

    // Loop through each edge of the polygon
    for (int i = 0; i < NumSides; i++) {
        // Calculate the coordinates of two consecutive vertices
        double angle1 = initialAngle + i * angleStep;
        double angle2 = initialAngle + (i + 1) * angleStep;
        Point p1 = { Center.x + Radius * cos(angle1), Center.y + Radius * sin(angle1) };
        Point p2 = { Center.x + Radius * cos(angle2), Center.y + Radius * sin(angle2) };

        // Ray-casting: Check if the point lies on the correct side of the edge
        if (((p1.y > y) != (p2.y > y)) &&
            (x < (p2.x - p1.x) * (y - p1.y) / (p2.y - p1.y + 1e-10) + p1.x)) {
            inside = !inside;
        }
    }
    return inside;
}

string RegularPoly::GetShapeType() const
{
    return "RegularPoly";
}

void RegularPoly::Rotate(double degrees)
{
    // This function rotates the polygon by exactly 90 degrees (as per project requirement)
    // Since only 90-degree rotation is required, we use a fixed angle
    const double PI = 3.14159265358979323846;
    double radians = 90.0 * PI / 180.0; // Convert 90 degrees to radians

    // Step 1: Calculate the relative position of the Vertex with respect to the Center
    double dx = Vertex.x - Center.x;
    double dy = Vertex.y - Center.y;

    // Step 2: Apply 90-degree rotation matrix to the relative coordinates
    Vertex.x = Center.x - dy;
    Vertex.y = Center.y + dx;
}

shape* RegularPoly::Clone()
{
    return new RegularPoly(*this);
}

void RegularPoly::Move(int dx, int dy)
{
    Center.x += dx;
    Center.y += dy;
    Vertex.x += dx;
    Vertex.y += dy;
}

void RegularPoly::Scale(double factor)
{
    // Scale the radius
    Radius *= factor;
    
    // Update the vertex point to maintain the same direction from center
    double dx = Vertex.x - Center.x;
    double dy = Vertex.y - Center.y;
    double distance = sqrt(dx * dx + dy * dy);
    
    if (distance > 0) {
        // Normalize and scale
        dx = (dx / distance) * Radius;
        dy = (dy / distance) * Radius;
        Vertex.x = Center.x + dx;
        Vertex.y = Center.y + dy;
    }
}

void RegularPoly::Save(ofstream& OutFile)
{
    OutFile << "RegularPoly " << Center.x << " " << Center.y << " " << Vertex.x << " " << Vertex.y << " " << NumSides << endl;
    OutFile << (int)ShpGfxInfo.DrawClr.ucRed << " " << (int)ShpGfxInfo.DrawClr.ucGreen << " " << (int)ShpGfxInfo.DrawClr.ucBlue << endl;
    OutFile << (int)ShpGfxInfo.FillClr.ucRed << " " << (int)ShpGfxInfo.FillClr.ucGreen << " " << (int)ShpGfxInfo.FillClr.ucBlue << endl;
    OutFile << ShpGfxInfo.isFilled << endl;
    OutFile << Radius << endl;
}

void RegularPoly::Load(ifstream& Infile)
{
    Infile >> Center.x >> Center.y >> Vertex.x >> Vertex.y >> NumSides;
  
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

Point RegularPoly::Getcenter() const
{
    return Center;
}
void RegularPoly::Resize(double newWidth, double newHeight)
{
    // Resize is not applicable for regular polygons in the same way as rectangles or squares
    // We will adjust the radius based on the average of newWidth and newHeight
    Radius = (newWidth + newHeight) / 4.0; // Average to maintain a regular shape
    // Update the vertex position accordingly
    double dx = Vertex.x - Center.x;
    double dy = Vertex.y - Center.y;
    double distance = sqrt(dx * dx + dy * dy);
    
    if (distance > 0) {
        // Normalize and scale
        dx = (dx / distance) * Radius;
        dy = (dy / distance) * Radius;
        Vertex.x = Center.x + dx;
        Vertex.y = Center.y + dy;
    }
}
void RegularPoly::Save(ofstream& OutFile)
{
    OutFile << "RegularPoly " << Center.x << " " << Center.y << " " << Vertex.x << " " << Vertex.y << " " << NumSides << endl;
    OutFile << (int)ShpGfxInfo.DrawClr.ucRed << " " << (int)ShpGfxInfo.DrawClr.ucGreen << " " << (int)ShpGfxInfo.DrawClr.ucBlue << endl;
    OutFile << (int)ShpGfxInfo.FillClr.ucRed << " " << (int)ShpGfxInfo.FillClr.ucGreen << " " << (int)ShpGfxInfo.FillClr.ucBlue << endl;
    OutFile << ShpGfxInfo.isFilled << endl;
    OutFile << Radius << endl;
}
void RegularPoly::Load(ifstream& Infile)
{
    Infile >> Center.x >> Center.y >> Vertex.x >> Vertex.y >> NumSides;
  
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