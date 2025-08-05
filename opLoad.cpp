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


opLoad::opLoad(controller* pCont) : operation(pCont)
{}

opLoad::~opLoad()
{}

void opLoad::Execute()
{
	// Get the controller and GUI
	GUI* pUI = pControl->GetUI();
	Graph* pGraph = pControl->getGraph();

	// Ask user for filename
	pUI->PrintMessage("Enter filename to load to (without extension):");
	string name = pUI->GetSrting();  // or GetString() if that's the correct spelling
	if (name == "") { pUI->PrintMessage("Load cancelled"); return; }
	name += ".txt";

	// Open the file for reading
	ifstream Infile(name);
	if (!Infile.is_open())
	{
		pUI->PrintMessage("Error: Could not open file " + name);
		return;
	}
	else 
	{
		pUI->PrintMessage("Loading shapes from " + name);
		pGraph->load(Infile); // Load shapes from the file
    }
	
	Infile.close(); // Close the file after reading
	pUI->PrintMessage("Shapes loaded successfully from " + name);
	// Update the interface to reflect the loaded shapes
	pControl->UpdateInterface(); // Refresh the interface to reflect loaded shapes
}
