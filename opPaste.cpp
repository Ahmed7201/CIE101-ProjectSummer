#include "opPaste.h"
#include "controller.h"
#include "Shapes/Graph.h"


opPaste::opPaste(controller* pCont) : operation(pCont) {}

void opPaste::Execute() {
    Graph* pGraph = pControl->getGraph();
	GUI* pUI = pControl->GetUI();
	shape* clickedShape = pGraph->GetSelectedShape();
	if (clickedShape) {
		// Add the cloned shape to the graph
		pGraph->PasteCopiedShape(clickedShape);
		pUI->PrintMessage("Shape Pasted successfully");
	}
	else {
		pUI->PrintMessage("No shape selected to paste");
	}
	pControl->UpdateInterface(); // Refresh the interface to reflect changes
}

