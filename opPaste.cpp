#include "opPaste.h"
#include "controller.h"
#include "Shapes/Graph.h"


opPaste::opPaste(controller* pCont) : operation(pCont) {}

void opPaste::Execute() {
	Point clickedPoint;
    Graph* pGraph = pControl->getGraph();
	GUI* pUI = pControl->GetUI();
	shape* clickedShape = pGraph->GetSelectedShape();
	if (clickedShape) {
		pUI->PrintMessage("Click at where you want to paste the copied shape : ");
		pUI->GetPointClicked(clickedPoint.x, clickedPoint.y); // Get the point where the user clicked
		// Add the cloned shape to the graph
		pGraph->PasteCopiedShape(clickedPoint);
		pUI->PrintMessage("Shape Pasted successfully");
	}
	else {
		pUI->PrintMessage("No shape selected to paste");
	}
	pControl->UpdateInterface(); // Refresh the interface to reflect changes
}

