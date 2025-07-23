#include "opSelect.h"
#include "controller.h"
#include "GUI/GUI.h"

opSelect::opSelect(controller* pCont) : operation(pCont)
{
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
	pUI->GetPointClicked(clickedPoint.x, clickedPoint.y); // Get the point clicked by the user
	// Get the shape at the clicked point
	shape* selectedShape = pGraph->Getshape(clickedPoint.x,clickedPoint.y);
	if (selectedShape)
	{
		if(selectedShape->IsSelected()==false)
		{
			selectedShape->SetSelected(true); // Select the shape
			pUI->PrintMessage("Shape selected ");
		}
		
	}
	else
	{
		pUI->PrintMessage("No shape found ");
	}
}