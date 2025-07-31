#include "Line.h"
#include <fstream>

Line::Line(Point P1, Point P2, GfxInfo shapeGfxInfo) :shape(shapeGfxInfo)
{
	point1 = P1;
	point2 = P2;
}

Line::~Line()
{
}

void Line::Draw(GUI* pUI) const
{
	//Call Output::DrawSquare to draw a Line on the screen	
	pUI->DrawLine(point1, point2, ShpGfxInfo);
}
bool Line::isInside(int x, int y) const
{
    int x1 = point1.x, y1 = point1.y;
    int x2 = point2.x, y2 = point2.y;

    // Length of the line segment
    double lineLength = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));

    // If the line is too short, use a simple distance check from the midpoint
    if (lineLength < 1.0) {
        double dist = sqrt((x - (x1 + x2) / 2) * (x - (x1 + x2) / 2) + (y - (y1 + y2) / 2) * (y - (y1 + y2) / 2));
        return dist <= ShpGfxInfo.BorderWdth / 2.0 + 1.0; // Tolerance
    }

    // Project the point onto the line segment
    double t = ((x - x1) * (x2 - x1) + (y - y1) * (y2 - y1)) / (lineLength * lineLength);
    t = max(0.0, min(1.0, t)); // Clamp t to [0, 1] to stay within the segment

    // Closest point on the line segment
    double closestX = x1 + t * (x2 - x1);
    double closestY = y1 + t * (y2 - y1);

    // Distance from the point to the closest point on the line
    double distance = sqrt((x - closestX) * (x - closestX) + (y - closestY) * (y - closestY));

    // Tolerance: Use half the border width plus a small buffer (e.g., 1 pixel) for click area
    double tolerance = ShpGfxInfo.BorderWdth / 2.0 + 1.0;

    return distance <= tolerance;
	
}
string Line::GetShapeType() const
{
	return "Line"; // Return the shape type as a string
}
void Line::Rotate(double degrees)
{
    // Use a constant for pi since M_PI might not be defined
    const double PI = 3.14159265358979323846;
    // Convert degrees to radians
    double radians = degrees * PI / 180.0;

    // Calculate the center of the line (midpoint of point1 and point2)
    double centerX = (point1.x + point2.x) / 2.0;
    double centerY = (point1.y + point2.y) / 2.0;

    // Rotate point1 around the center
    double x = point1.x - centerX;
    double y = point1.y - centerY;
    point1.x = centerX + (x * cos(radians) - y * sin(radians));
    point1.y = centerY + (x * sin(radians) + y * cos(radians));

    // Rotate point2 around the center
    x = point2.x - centerX;
    y = point2.y - centerY;
    point2.x = centerX + (x * cos(radians) - y * sin(radians));
    point2.y = centerY + (x * sin(radians) + y * cos(radians));
}
shape* Line::Clone()
{
    // Cloning is not implemented for Line
    return new Line(point1, point2, ShpGfxInfo);
}
void Line::Save(ofstream& OutFile)
{
    // Save the line parameters to the file
    OutFile << point1.x << " " << point1.y << " " << point2.x << " " << point2.y << endl;
    OutFile << ShpGfxInfo.DrawClr.ucRed << " " << ShpGfxInfo.DrawClr.ucGreen << " " << ShpGfxInfo.DrawClr.ucBlue << endl;
    OutFile << ShpGfxInfo.FillClr.ucRed << " " << ShpGfxInfo.FillClr.ucGreen << " " << ShpGfxInfo.FillClr.ucBlue << endl;
    OutFile << ShpGfxInfo.isFilled << endl;
}
void Line::Load(ifstream& Infile)
{
    // Load the line parameters from the file
    Infile >> point1.x >> point1.y >> point2.x >> point2.y;
    Infile >> ShpGfxInfo.DrawClr.ucRed >> ShpGfxInfo.DrawClr.ucGreen >> ShpGfxInfo.DrawClr.ucBlue;
    Infile >> ShpGfxInfo.FillClr.ucRed >> ShpGfxInfo.FillClr.ucGreen >> ShpGfxInfo.FillClr.ucBlue;
    Infile >> ShpGfxInfo.isFilled;
}
