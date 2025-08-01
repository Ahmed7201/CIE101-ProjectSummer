#include "opSave.h"
#include "controller.h"
#include "GUI/GUI.h"
#include <fstream>
#include <filesystem> // C++17 and later
using namespace std;
namespace fs = filesystem;

opSave::opSave(controller* pCont) : operation(pCont)
{
}

opSave::~opSave()
{
}

void opSave::Execute()
{
	GUI* pUI = pControl->GetUI();
	Graph* pGraph = pControl->getGraph();

	// Ask user for filename
	pUI->PrintMessage("Enter filename to save to (without extension):");
	string name = pUI->GetSrting();  // or GetString() if that's the correct spelling
	name += ".txt";

	// Create full path using current directory
	fs::path fullPath = fs::current_path() / name;

	ofstream OutFile(fullPath);
	if (!OutFile.is_open())
	{
		pUI->PrintMessage("Error: Could not open file " + fullPath.string());
		return;
	}

	// Save the shapes
	pUI->PrintMessage("Saving shapes to file...");
	pGraph->Save(OutFile);
	OutFile.close();

	pUI->PrintMessage("Shapes saved to:\n" + fullPath.string());
}
