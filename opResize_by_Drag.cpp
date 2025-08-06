#include "opResize_by_Drag.h"
#include "controller.h"
#include "GUI/GUI.h"

opResize_by_Drag::opResize_by_Drag(controller* pCont) : operation(pCont) {}

opResize_by_Drag::~opResize_by_Drag() {}

void opResize_by_Drag::Execute()
{
	GUI* pUI = pControl->GetUI();
	Graph* pGraph = pControl->getGraph();
	shape* selected = pGraph->GetSelectedShape();
	if (!selected)
	{
		pUI->PrintMessage("Please select a shape first.");
		return;
	}
	int startX, startY;
	pUI->GetPointClicked(startX, startY);
	pUI->PrintMessage("Click and hold to resize the shape...");
	// Wait until mouse button is pressed
	while (!pUI->IsMouseButtonDown())
	{
		// do nothing, just wait
	}
	// While resizing
	int currentX = startX, currentY = startY;
	while (pUI->IsMouseButtonDown())
	{
		int newX, newY;
		pUI->GetMouseCoord(newX, newY);
		// Only resize if the cursor has changed position
		if (newX != currentX || newY != currentY)
		{
			int dx = newX - currentX;
			int dy = newY - currentY;
			selected->Resize(dx, dy); // resize by delta
			currentX = newX;
			currentY = newY;
			pControl->UpdateInterface(); // update drawing!
		}
	}
	pUI->PrintMessage("Shape resized.");
}
