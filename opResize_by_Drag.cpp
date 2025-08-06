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
	
	pUI->PrintMessage("Click and drag to resize the shape...");
	
	// Get initial click position
	int startX, startY;
	pUI->GetPointClicked(startX, startY);
	
	// Wait until mouse button is pressed
	while (!pUI->IsMouseButtonDown())
	{
		// do nothing, just wait
	}
	
	// Get initial shape dimensions (approximate)
	int initialWidth = 50;  // Default initial width
	int initialHeight = 50; // Default initial height
	
	// While resizing
	int currentX = startX, currentY = startY;
	do
	{
		int newX, newY;
		pUI->GetMouseCoord(newX, newY);
		
		// Only resize if the cursor has changed position
		if (newX != currentX || newY != currentY)
		{
			// Calculate the distance moved
			int deltaX = newX - startX;
			int deltaY = newY - startY;
			
			// Calculate new dimensions based on movement
			double newWidth = initialWidth + deltaX;
			double newHeight = initialHeight + deltaY;
			
			// Ensure minimum size
			if (newWidth < 10) newWidth = 10;
			if (newHeight < 10) newHeight = 10;
			
			// Resize the shape with new dimensions
			selected->Resize(newWidth, newHeight);
			
			currentX = newX;
			currentY = newY;
			pControl->UpdateInterface(); // update drawing!
		}
	} while (pUI->IsMouseButtonDown());

	pUI->PrintMessage("Shape resized.");
}
