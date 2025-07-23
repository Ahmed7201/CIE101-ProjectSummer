#include "opSelect.h"
#include "controller.h"
#include "GUI/GUI.h"

opSelect::opSelect(controller* pCont) : operation(pCont)
{
	selectedShape = nullptr; // Initialize selectedShape to nullptr
	
}
opSelect::~opSelect()
{
	// Destructor
}
void opSelect::Execute()
{
	Point clickedPoint;
	GUI* pUI = pControl->GetUI();
	Graph* pGraph = pControl->getGraph();
	// Clear the status bar
	pUI->ClearStatusBar();
	// Get the shape at the clicked point
	selectedShape = pGraph->Getshape(clickedPoint.x,clickedPoint.y);
	if (selectedShape)
	{
		if(selectedShape->IsSelected()==false)
		{
			selectedShape->SetSelected(true); // Select the shape
			pUI->PrintMessage("Shape selected");
		}
		
	}
	else
	{
		pUI->PrintMessage("No shape found ");
	}
}