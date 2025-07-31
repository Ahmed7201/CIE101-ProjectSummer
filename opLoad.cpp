#include "opLoad.h"
#include "controller.h"
#include "GUI/GUI.h"
#include "Shapes/Rect.h"
#include "Square.h"
#include "Triangle.h"
#include "Oval.h"
#include "Circle.h"
#include "Line.h"
#include <fstream>


opLoad::opLoad(controller* pCont, string fileName) : operation(pCont), filename(fileName)
{}

opLoad::~opLoad()
{}

void opLoad::Execute()
{
	// Get the controller and GUI
	GUI* pUI = pControl->GetUI();
	Graph* pGraph = pControl->getGraph();
	// Open the file for reading
	ifstream Infile(filename);
	if (!Infile.is_open())
	{
		pUI->PrintMessage("Error: Could not open file " + filename);
		return;
	}
	// Clear existing shapes in the controller
	pUI->ClearDrawArea(); // Clear the drawing area
	// Read shapes from the file
	string shapeType;
	while (Infile >> shapeType)
	{
		shape* newShape = nullptr;
		if (shapeType == "Rectangle")
		{
			newShape = new Rect(Point(), Point(), GfxInfo());
		}
		else if (shapeType == "Square")
		{
			newShape = new Square(Point(), Point(), GfxInfo());
		}
		else if (shapeType == "Triangle")
		{
			newShape = new Triangle(Point(), Point(), Point(), GfxInfo());
		}
		else if (shapeType == "Oval")
		{
			newShape = new Oval(Point(), Point(), GfxInfo());
		}
		else if (shapeType == "Circle")
		{
			newShape = new Circle(Point(), Point(), GfxInfo());
		}
		else if (shapeType == "Line")
		{
			newShape = new Line(Point(), Point(), GfxInfo());
		}
		if (newShape)
		{
			newShape->Load(Infile); // Load shape parameters from the file
			pGraph->Addshape(newShape); // Add the shape to the controller
		}
	}
	Infile.close(); // Close the file after reading
	pUI->PrintMessage("Shapes loaded successfully from " + filename);
	pControl->UpdateInterface(); // Refresh the interface to reflect loaded shapes
}
