#include "opSendtoBack.h"
#include "controller.h"
#include "GUI/GUI.h"

opSendtoBack::opSendtoBack(controller* pCont) : operation(pCont)
{
}
opSendtoBack::~opSendtoBack()
{
}
void opSendtoBack::Execute() {
	GUI* pUI = pControl->GetUI();
	Graph* pGraph = pControl->getGraph();

	// Get the currently selected shape
	shape* clickedShape = pGraph->GetSelectedShape();

	if (clickedShape) {
		// Remove the selected shape from the graph
		pGraph->SendToBack(clickedShape);
		pUI->PrintMessage("Shape sent to back successfully");
	}
	else {
		pUI->PrintMessage("No shape selected to send to back");
	}

	pControl->UpdateInterface(); // Refresh the interface to reflect changes
}