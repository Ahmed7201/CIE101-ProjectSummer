#include "Line.h"

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