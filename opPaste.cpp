#include "opPaste.h"
#include "controller.h"
#include "Shapes/Graph.h"


opPaste::opPaste(controller* pCont) : operation(pCont) {}

opPaste::~opPaste() {}

void opPaste::Execute() {
	Graph* pGraph = pControl->getGraph();
	pGraph->PushToUndo();
	Point clickedPoint;
	GUI* pUI = pControl->GetUI();
	shape* clickedShape = pGraph->GetSelectedShape();
	if (clickedShape) {
		pUI->PrintMessage("Click at where you want to paste the copied shape : ");
		pUI->GetPointClicked(clickedPoint.x, clickedPoint.y); 
		
		pGraph->PasteCopiedShape(clickedPoint);
		pUI->PrintMessage("Shape Pasted successfully");
	}
	else {
		pUI->PrintMessage("No shape selected to paste");
	}
	pControl->UpdateInterface(); 
}

