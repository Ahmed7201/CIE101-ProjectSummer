#pragma once  
#include "Shapes/Shape.h"  
class Circle :  
    public shape  
{  
private:  
    Point Center; // Center of the circle  
    Point Edge_Point; // Point on the circumference of the circle  
    double Radius; // Radius of the circle  
public:  
    Circle(Point P1, Point P2, GfxInfo shapeGfxInfo); // Constructor  
    virtual ~Circle(); // Destructor  
    virtual void Draw(GUI* pUI) const; // Draw the circle on the UI  
    void SetRadius(int r); // Set the radius of the circle  
    double GetRadius() const; // Get the radius of the circle  
    Point GetCenter() const; // Get the center of the circle  
    virtual bool isInside(int x, int y) const override;  
    virtual string GetShapeType() const override;  
	virtual void Rotate(double degrees) override; // Rotate the circle by a given angle
	virtual shape* Clone() override; // Cloning is not implemented for Circle
	virtual void Move(int dx, int dy) override; // Move the circle by dx, dy
	virtual void Save(ofstream& OutFile) override; // Save the circle parameters to a file
	virtual void Load(ifstream& Infile) override; // Load the circle parameters from a file
	virtual Point Getcenter() const override; // Get the center point of the circle
}; // Add missing semicolon here
