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
		// Clone the selected shape
		shape* clonedShape = clickedShape->Clone();
		if (clonedShape) {
			// Add the cloned shape to the graph
			pGraph->Addshape(clonedShape);
			pUI->PrintMessage("Shape copied successfully");
		} else {
			pUI->PrintMessage("Error: Could not clone the shape");
		}
	} else {
		pUI->PrintMessage("No shape selected to copy");
	}
	pControl->UpdateInterface(); // Refresh the interface to reflect changes
}
