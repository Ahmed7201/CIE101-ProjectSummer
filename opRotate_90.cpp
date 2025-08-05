#include "opRotate_90.h"
#include "controller.h"
#include "GUI/GUI.h"

opRotate_90::opRotate_90(controller* pCont) : operation(pCont) 
{}

opRotate_90::~opRotate_90() 
{}

void opRotate_90::Execute() {
	Graph* pGraph = pControl->getGraph();
	pGraph->PushToUndo();
	GUI* pUI = pControl->GetUI();

	// Get the currently selected shape
	shape* clickedShape = pGraph->GetSelectedShape();
	if (clickedShape) {
		pGraph->RotateSelectedShape(clickedShape); // Rotate the selected shape by 90 degrees
		pUI->PrintMessage("Shape rotated 90 degrees successfully");
	} else {
		pUI->PrintMessage("No shape selected to rotate");
	}
	pControl->UpdateInterface(); // Refresh the interface to reflect changes
}