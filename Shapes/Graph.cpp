#include "Graph.h"
#include "../GUI/GUI.h"

Graph::Graph()
{
	shapeCount = 0;
	selectedShape = nullptr;
}

Graph::~Graph()
{
}

//==================================================================================//
//						shapes Management Functions								//
//==================================================================================//

//Add a shape to the list of shapes
void Graph::Addshape(shape* pShp)
{
	//Add a new shape to the shapes list
	if(shapeCount<maxShapeCount)
		shapesList[shapeCount++] = pShp;
}
////////////////////////////////////////////////////////////////////////////////////
//Draw all shapes on the user interface
void Graph::Draw(GUI* pUI) const
{
	pUI->ClearDrawArea();
	for (int i=0;i<shapeCount; i++)
		shapesList[i]->Draw(pUI);
}
void Graph::UnselectAllShapes(GUI* pUI) {
	if (selectedShape) {
		selectedShape->SetSelected(false);
		GfxInfo gfxInfo = selectedShape->GetGfxInfo();
		gfxInfo.DrawClr = pUI->getCrntDrawColor(); // Reset to original color
		selectedShape->SetGfxInfo(gfxInfo); // Update GfxInfo
		selectedShape->Draw(pUI); // Redraw to remove highlight
		selectedShape = nullptr;
	}
	for (int i = 0; i < shapeCount; i++) {
		if (shapesList[i] && shapesList[i] != selectedShape && shapesList[i]->IsSelected()) {
			shapesList[i]->SetSelected(false);
			GfxInfo gfxInfo = shapesList[i]->GetGfxInfo();
			gfxInfo.DrawClr = pUI->getCrntDrawColor(); // Reset to original color
			shapesList[i]->SetGfxInfo(gfxInfo); // Update GfxInfo
			shapesList[i]->Draw(pUI);
		}
	}
}
void Graph::SetSelectedShape(shape* shape)
{
	// Set the currently selected shape
	selectedShape = shape;
	if (selectedShape) {
		selectedShape->SetSelected(true);
	}
}
shape* Graph::GetSelectedShape() const
{
	// Return the currently selected shape
	return selectedShape;
}


shape* Graph::Getshape(int x, int y) const
{
	//If a shape is found return a pointer to it.
	//if this point (x,y) does not belong to any shape return NULL
	for (int i = shapeCount - 1; i >= 0; i--) {
		if (shapesList[i] && shapesList[i]->isInside(x, y)) {
			return shapesList[i];
		}
	}
	

	///Add your code here to search for a shape given a point x,y	

	return nullptr;
}
