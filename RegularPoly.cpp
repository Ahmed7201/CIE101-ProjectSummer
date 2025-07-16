#include "RegularPoly.h"
#include <cmath>

const double PI = 3.141592653589793;

RegularPoly::RegularPoly(Point center, Point edgePoint, int sides, GfxInfo shapeGfxInfo)
    : shape(shapeGfxInfo), Center(center), numSides(sides)
{
    double dx = edgePoint.x - center.x;
    double dy = edgePoint.y - center.y;
    double radius = sqrt(dx * dx + dy * dy);
    double initialAngle = atan2(dy, dx);
    double angleStep = 2 * PI / numSides;

    XCoords = new int[numSides];
    YCoords = new int[numSides];

    for (int i = 0; i < numSides; i++) {
        double currentAngle = initialAngle + i * angleStep;
        XCoords[i] = (center.x + radius * cos(currentAngle));
        YCoords[i] = (center.y + radius * sin(currentAngle));
    }
}

RegularPoly::~RegularPoly()
{
    delete[] XCoords;
    delete[] YCoords;
}

void RegularPoly::Draw(GUI* pUI) const
{
    // Draw the polygon using CMU graphics DrawPolygon
    pUI->pWind->SetPen(ShpGfxInfo.DrawClr, ShpGfxInfo.BorderWdth);

    if (ShpGfxInfo.isFilled)
        pUI->pWind->SetBrush(ShpGfxInfo.FillClr);

    pUI->pWind->DrawPolygon(XCoords, YCoords, numSides, ShpGfxInfo.isFilled ? FILLED : FRAME);
}
