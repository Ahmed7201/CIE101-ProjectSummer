#include "opCopy.h"
#include "controller.h"
#include "GUI/GUI.h"

opCopy::opCopy(controller* pCont) : operation(pCont)
{}

opCopy::~opCopy()
{}

void opCopy::Execute()
{
	GUI* pUI = pControl->GetUI();
	Graph* pGraph = pControl->getGraph();
	// Get the currently selected shape
	shape* clickedShape = pGraph->GetSelectedShape();
	if (clickedShape) {
		// Add the cloned shape to the graph
	    pGraph->CopySelectedShape(clickedShape);
		pUI->PrintMessage("Shape copied successfully");
	} else {
		pUI->PrintMessage("No shape selected to copy");
	}
	pControl->UpdateInterface(); // Refresh the interface to reflect changes
}
