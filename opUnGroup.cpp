#include "opUnGroup.h"
#include "controller.h"
#include "GUI/GUI.h"
#include "Shapes/Graph.h"
#include "Shapes/shape.h"

opUnGroup::opUnGroup(controller* pCont) : operation(pCont)
{
}

opUnGroup::~opUnGroup()
{
}

void opUnGroup::Execute()
{
	GUI* pUI = pControl->GetUI();
	Graph* pGraph = pControl->getGraph();

	// Get  selected shape
	shape* selectedShape = pGraph->GetSelectedShape();
	if (!selectedShape) {
		pUI->PrintMessage("No shape selected. Please select a group to ungroup.");
		return;
	}

	// Check  group
	if (!selectedShape->IsGroup()) {
		pUI->PrintMessage("Selected shape is not a group. Please select a group to ungroup.");
		return;
	}

	// Ungroup
	bool success = pGraph->UnGroupShape(selectedShape);
	
	if (success) {
		pUI->PrintMessage("Group ungrouped successfully.");
	} else {
		pUI->PrintMessage("Failed to ungroup. Please try again.");
	}
} 