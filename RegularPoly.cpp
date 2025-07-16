#include "RegularPoly.h"

RegularPoly::RegularPoly(Point P1, Point P2, Point P3, Point P4, Point P5, GfxInfo shapeGfxInfo) :shape(shapeGfxInfo)
{
	Corner1 = P1;
	Corner2 = P2;
}

RegularPoly::~RegularPoly()
{
}

void RegularPoly::Draw(GUI* pUI) const
{
	//Call Output::DrawRegularPoly to draw a RegularPolyangle on the screen	
	pUI->DrawRegularPoly(Corner1, Corner2, ShpGfxInfo);
}
