#include "Graph.h"
#include "../GUI/GUI.h"
#include "../Shapes/Rect.h"
#include "../Square.h"
#include "../Triangle.h"
#include "../Oval.h"
#include "../Circle.h"
#include "../Line.h"
#include <fstream>

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
		
		selectedShape = nullptr;
	}
	for (int i = 0; i < shapeCount; i++) {
		if (shapesList[i] && shapesList[i] != selectedShape && shapesList[i]->IsSelected()) {
			shapesList[i]->SetSelected(false);
			GfxInfo gfxInfo = shapesList[i]->GetGfxInfo();
			gfxInfo.DrawClr = pUI->getCrntDrawColor(); // Reset to original color
			shapesList[i]->SetGfxInfo(gfxInfo); // Update GfxInfo
			
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
void Graph::RemoveShape(shape* pShape)
{
	for (int i = 0;i < shapeCount;i++)
	{
		if (shapesList[i] == pShape)
		{
			for (int j = i;j < shapeCount;j++)
			{
				shapesList[j] = shapesList[j + 1];
			}
			shapeCount--;
			
		}
	}
}
void Graph::SendToBack(shape* pShape) {
	for (int i = 0; i < shapeCount; ++i) {
		if (shapesList[i]->IsSelected()) {
			pShape = shapesList[i]; // pointer to the selected shape

			// this is start from the i of the selected object then goes back like the car and each one meet behind it she put it in the place she is in now and looping
			for (int j = i; j > 0; --j) {
				shapesList[j] = shapesList[j - 1];
			}

			// this is to make the selected on the zero place after shigting all of them to the righttt
			shapesList[0] = selectedShape;

			break; 
		}
	}
};
void Graph::RotateSelectedShape(shape* pShape) {
	if (selectedShape) {
		selectedShape->Rotate(90.0); // Rotate the selected shape by 90 degrees
	}
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
void Graph::CopySelectedShape(shape* pShape)
{
	if (selectedShape && shapeCount < maxShapeCount) {
		
		shape* newshape = selectedShape->Clone();      // Deep copy
	}
}
void Graph::PasteCopiedShape(Point P1) {
	if (selectedShape && shapeCount < maxShapeCount) {
		shape* newshape = selectedShape->Clone(); // Clone the copied shape
		if (newshape) {
			// Adjust position based on the paste point
			Point originalPoint = newshape->Getcenter(); // Assume first point as reference
			newshape->Move(P1.x - originalPoint.x, P1.y - originalPoint.y); // Move relative to original position
			Addshape(newshape); // Add to shapesList
		}
	
	}
}

void Graph::Save(ofstream& outfile)
{
	// Save the number of shapes
	outfile << shapeCount << endl;
	// Save each shape
	for (int i = 0; i < shapeCount; i++) {
		shapesList[i]->Save(outfile);
	}
}
void Graph::load(ifstream& inputfile)
{
	// Clear the existing shapes
	for (int i = 0; i < shapeCount; i++) {
		delete shapesList[i];
	}
	shapeCount = 0;
	// Read the number of shapes
	inputfile >> shapeCount;
	for (int i = 0; i < shapeCount; i++) {
		string shapeType;
		while (inputfile >> shapeType)
		{
			shape* newShape = nullptr;
			if (shapeType == "Rectangle")
			{
				newShape = new Rect(Point(), Point(), GfxInfo());
			}
			else if (shapeType == "Square")
			{
				newShape = new Square(Point(), Point(), GfxInfo());
			}
			else if (shapeType == "Triangle")
			{
				newShape = new Triangle(Point(), Point(), Point(), GfxInfo());
			}
			else if (shapeType == "Oval")
			{
				newShape = new Oval(Point(), Point(), GfxInfo());
			}
			else if (shapeType == "Circle")
			{
				newShape = new Circle(Point(), Point(), GfxInfo());
			}
			else if (shapeType == "Line")
			{
				newShape = new Line(Point(), Point(), GfxInfo());
			}
			if (newShape)
			{
				newShape->Load(inputfile); // Load shape parameters from the file
				Addshape(newShape); // Add the shape to the controller
			}
		}
		
	}
}
