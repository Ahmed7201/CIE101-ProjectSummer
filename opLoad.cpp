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
	else 
	{
		pUI->PrintMessage("Loading shapes from " + filename);
		pGraph->load(Infile); // Load shapes from the file
    }
	
	Infile.close(); // Close the file after reading
	pUI->PrintMessage("Shapes loaded successfully from " + filename);
	pControl->UpdateInterface(); // Refresh the interface to reflect loaded shapes
}
