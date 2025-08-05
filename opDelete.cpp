#include "opDelete.h"
#include "controller.h"
#include "GUI/GUI.h"

opDelete::opDelete(controller* pCont) : operation(pCont) 
{}
opDelete::~opDelete() 
{}
void opDelete::Execute() {
	Graph* pGraph = pControl->getGraph();
	pGraph->PushToUndo();
	GUI* pUI = pControl->GetUI();
	
	
	// Get the currently selected shape
	shape* clickedShape = pGraph->GetSelectedShape();
	
	if (clickedShape) {
		// Remove the selected shape from the graph
		pGraph->RemoveShape(clickedShape);
		pGraph->SetSelectedShape(nullptr); // Clear the selected shape
		pUI->PrintMessage("Shape deleted successfully");
	} else {
		pUI->PrintMessage("No shape selected to delete");
	}
	
	pControl->UpdateInterface(); // Refresh the interface to reflect changes
}