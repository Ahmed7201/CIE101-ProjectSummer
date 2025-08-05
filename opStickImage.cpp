#include "opStickImage.h"
#include "controller.h"
#include "GUI/GUI.h"
#include "Shapes/Graph.h"
#include "Shapes/shape.h"

opStickImage::opStickImage(controller* pCont) : operation(pCont)
{
}

opStickImage::~opStickImage()
{
}

void opStickImage::Execute()
{
	GUI* pUI = pControl->GetUI();
	Graph* pGraph = pControl->getGraph();

	// Get the currently selected shape
	shape* selectedShape = pGraph->GetSelectedShape();
	if (!selectedShape) {
		pUI->PrintMessage("No shape selected. Please select a shape first.");
		return;
	}

	// Check if the shape already has an image
	if (selectedShape->HasImage()) {
		pUI->PrintMessage("The selected shape already has an image attached.");
		return;
	}

	// Ask user for image filename
	pUI->PrintMessage("Enter image filename (e.g., image1.jpg): ");
	string filename = pUI->GetSrting();
	
	if (filename.empty()) {
		pUI->PrintMessage("Operation cancelled.");
		return;
	}

	// Construct the full path to the image
	string fullPath = "images\\Shape_Images\\" + filename;
	
	// Set the image path for the selected shape
	selectedShape->SetImagePath(fullPath);
	
	pUI->PrintMessage("Image '" + filename + "' attached to the selected shape successfully.");
} 