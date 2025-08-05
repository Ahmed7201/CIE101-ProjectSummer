#include "opStickImage.h"
#include "controller.h"
#include "GUI/GUI.h"
#include "Shapes/Graph.h"
#include "Shapes/shape.h"

opStickImage::opStickImage(controller* pCont) : operation(pCont) {}

opStickImage::~opStickImage() {}

void opStickImage::Execute()
{
	GUI* pUI = pControl->GetUI();
	Graph* pGraph = pControl->getGraph();

	shape* selectedShape = pGraph->GetSelectedShape();

	if (!selectedShape)
	{
		pUI->PrintMessage("No shape selected. Please select a shape first.");
		return;
	}


	pUI->PrintMessage("Enter image file name (e.g., image1.jpg):");
	string filename = pUI->GetSrting();

	string fullPath = "images\\Shape_Images\\" + filename;

	selectedShape->SetImagePath(fullPath);

	pUI->PrintMessage("Image added to the selected shape.");

	pControl->UpdateInterface(); // Refresh the interface to reflect changes
}
