#pragma once
#include "Shapes/Shape.h"
class Circle :
    public shape
{
private:
        Point Center; //Center of the circle
        Point Edge_Point; //Point on the circumference of the circle
		double Radius; //Radius of the circle
public:
            Circle(Point P1,Point P2, GfxInfo shapeGfxInfo); //Constructor
        virtual ~Circle(); //Destructor
        virtual void Draw(GUI* pUI) const; //Draw the circle on the UI
        void SetRadius(int r); //Set the radius of the circle
        double GetRadius() const; //Get the radius of the circle
        Point GetCenter() const; //Get the center of the circle

};

