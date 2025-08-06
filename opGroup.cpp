#include "opGroup.h"
#include "controller.h"
#include "GUI/GUI.h"
#include "Shapes/Graph.h"
#include "Shapes/shape.h"

opGroup::opGroup(controller* pCont) : operation(pCont)
{
}

opGroup::~opGroup()
{
}

void opGroup::Execute()
{
	GUI* pUI = pControl->GetUI();
	Graph* pGraph = pControl->getGraph();

	// Get the count of selected shapes
	int selectedCount = pGraph->GetSelectedShapesCount();
	
	if (selectedCount < 2) {
		pUI->PrintMessage("Please select at least 2 shapes to group.");
		return;
	}

	if (selectedCount > 10) {
		pUI->PrintMessage("Maximum 10 shapes can be grouped. Please select fewer shapes.");
		return;
	}

	// Group all selected shapes
	bool success = pGraph->GroupSelectedShapes();
	
	if (success) {
		pUI->PrintMessage("Grouped " + to_string(selectedCount) + " shapes successfully.");
	} else {
		pUI->PrintMessage("Failed to group shapes. Please try again.");
	}
} 