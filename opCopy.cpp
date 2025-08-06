#include "opCopy.h"
#include "controller.h"
#include "GUI/GUI.h"

opCopy::opCopy(controller* pCont) : operation(pCont)
{}

opCopy::~opCopy()
{}

void opCopy::Execute()
{
	Graph* pGraph = pControl->getGraph();
	pGraph->PushToUndo();
	GUI* pUI = pControl->GetUI();
	
	shape* clickedShape = pGraph->GetSelectedShape();
	if (clickedShape) {
	    pGraph->CopySelectedShape(clickedShape);
		pUI->PrintMessage("Shape copied successfully");
	} else {
		pUI->PrintMessage("No shape selected to copy");
	}
	pControl->UpdateInterface(); 
}
