#include "Graph.h"
#include "../GUI/GUI.h"
#include "../Shapes/Rect.h"
#include "../Square.h"
#include "../Triangle.h"
#include "../Oval.h"
#include "../Circle.h"
#include "../Line.h"
#include "../RegularPoly.h"
#include "../IrregularPoly.h"
#include "GroupShape.h"
#include <fstream>

Graph::Graph()
{
	shapeCount = 0;
	selectedShape = nullptr;
	isSaved = true;
	undoTop = -1;
	redoTop = -1;

	for (int i = 0; i < maxUndoRedo; i++) {
		undoStack[i] = nullptr;
		redoStack[i] = nullptr;
		shapeCountForUndo[i] = 0;
		shapeCountForRedo[i] = 0;
		}
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
	
	PushToUndoStack();
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
	SetSaved(false);
	

}
void Graph::SendToBack(shape* pShape) {
	PushToUndoStack();
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
	SetSaved(false);
	

};
void Graph::RotateSelectedShape(shape* pShape) {
	PushToUndoStack();
	if (selectedShape) {
		selectedShape->Rotate(90.0); // Rotate the selected shape by 90 degrees
	}
	SetSaved(false);
	

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
	PushToUndoStack();
	if (selectedShape && shapeCount < maxShapeCount) {
		
		shape* newshape = selectedShape->Clone();      
	}
	SetSaved(false);
	
}
void Graph::PasteCopiedShape(Point P1) {
	PushToUndoStack();
	if (selectedShape && shapeCount < maxShapeCount) {
		shape* newshape = selectedShape->Clone(); 
		if (newshape) {
			
			Point originalPoint = newshape->Getcenter(); 
			newshape->Move(P1.x - originalPoint.x, P1.y - originalPoint.y); 
			Addshape(newshape); 
		}
	
	}
	SetSaved(false);
	
}

void Graph::Save(ofstream& outfile)
{
	// Save the number of shapes
	outfile << shapeCount << endl;

	// Save each shape type and data
	for (int i = 0; i < shapeCount; i++) {
		string shapeType = shapesList[i]->GetShapeType();
		outfile << shapeType << endl;                 // Write type first
		shapesList[i]->Save(outfile);                 // Then write shape data
	}
}
bool Graph::IsSaved() const {
	return isSaved;
}

void Graph::SetSaved(bool saved) {
	isSaved = saved;
}

void Graph::PushToUndoStack() {
	if (undoTop < maxUndoRedo - 1) {
		undoTop++;
	}
	else {
		// Shift all previous states left (remove oldest)
		delete[] undoStack[0];
		for (int i = 1; i < maxUndoRedo; ++i) {
			undoStack[i - 1] = undoStack[i];
			shapeCountForUndo[i - 1] = shapeCountForUndo[i];
		}
		undoTop = maxUndoRedo - 1;
	}

	// Save current state
	undoStack[undoTop] = CloneAllShapes();
	shapeCountForUndo[undoTop] = shapeCount;

	// Clear redo history
	for (int i = 0; i <= redoTop; ++i) {
		delete[] redoStack[i];
		redoStack[i] = nullptr;
	}
	redoTop = -1;
}

shape** Graph::CloneAllShapes() {
	if (shapeCount <= 0 || shapeCount > maxShapeCount) return nullptr;

	shape** cloned = new shape * [shapeCount];
	for (int i = 0; i < shapeCount; ++i) {
		cloned[i] = shapesList[i]->Clone();  
	}
	return cloned;
}

void Graph::load(ifstream& inputfile)
{
	for(int i=0; i < shapeCount; ++i) {
		delete shapesList[i]; // Clean up existing shapes
		shapesList[i] = nullptr;
	}
	shapeCount = 0; // Reset shape count

	// Read how many shapes were saved
	int shapesToLoad = 0;
	if (!(inputfile >> shapesToLoad)) {
		// nothing to load or file format error
		return;
	}

	// For each saved shape read its type and load its data
	for (int i = 0; i < shapesToLoad; ++i)
	{
		string shapeType;
		if (!(inputfile >> shapeType)) {
			// unexpected EOF or read error
			break;
		}

		shape* pS = nullptr;

		if (shapeType == "Rectangle")
			pS = new Rect(Point(), Point(), GfxInfo());
		else if (shapeType == "Square")
			pS = new Square(Point(),Point(),GfxInfo());
		else if (shapeType == "Triangle")
			pS = new Triangle(Point(), Point(), Point(), GfxInfo());
		else if (shapeType == "Circle")
			pS = new Circle(Point(), Point(), GfxInfo());
		else if (shapeType == "Line")
			pS = new Line(Point(), Point(), GfxInfo());
		else if (shapeType == "Oval")
			pS = new Oval(Point(), Point(), GfxInfo());
		else if (shapeType == "RegularPolygon")
			pS = new RegularPoly(Point(), Point(),int(), GfxInfo());
		else if (shapeType == "IrregularPoly")
			pS = new IrregularPoly(nullptr, 0, GfxInfo());
		else {
			// Unknown shape type: skip the rest of this line to avoid being stuck
			string rest;
			getline(inputfile, rest);
			continue;
		}

		// Load the shape data from file
		if (pS) {
			pS->Load(inputfile);
			Addshape(pS); // Add the loaded shape to the shapes list
		}
	}
}
void Graph::PushToUndo() {
	if (undoTop < maxUndoRedo - 1) {
		undoStack[++undoTop] = CloneAllShapes();        
		shapeCountForUndo[undoTop] = shapeCount; 
		redoTop = -1;                                    
	}
}

void Graph::ClearShapes()
{
	for (int i = 0; i < shapeCount; i++)
	{
		delete shapesList[i];
		shapesList[i] = nullptr;
	}
	shapeCount = 0;
	selectedShape = nullptr;
}

// Group-related methods implementation
int Graph::GetSelectedShapesCount() const
{
	int count = 0;
	for (int i = 0; i < shapeCount; i++) {
		if (shapesList[i] && shapesList[i]->IsSelected()) {
			count++;
		}
	}
	return count;
}

shape* Graph::GetSelectedShape(int index) const
{
	int currentIndex = 0;
	for (int i = 0; i < shapeCount; i++) {
		if (shapesList[i] && shapesList[i]->IsSelected()) {
			if (currentIndex == index) {
				return shapesList[i];
			}
			currentIndex++;
		}
	}
	return nullptr;
}

bool Graph::GroupSelectedShapes()
{
	int selectedCount = GetSelectedShapesCount();
	
	if (selectedCount < 2) {
		return false;
	}
	
	if (selectedCount > 10) {
		selectedCount = 10; // Limit to 10 shapes
	}

	// Create array of selected shapes
	shape* selectedShapes[10];
	int count = 0;
	
	for (int i = 0; i < shapeCount && count < selectedCount; i++) {
		if (shapesList[i] && shapesList[i]->IsSelected()) {
			selectedShapes[count] = shapesList[i];
			count++;
		}
	}

	// Create a new group shape
	GfxInfo groupGfxInfo;
	groupGfxInfo.DrawClr = BLACK;
	groupGfxInfo.FillClr = WHITE;
	groupGfxInfo.isFilled = false;
	groupGfxInfo.BorderWdth = 2;
	groupGfxInfo.isSelected = false;

	GroupShape* groupShape = new GroupShape(selectedShapes, count, groupGfxInfo);

	// Remove the individual shapes from the list
	for (int i = 0; i < count; i++) {
		RemoveShape(selectedShapes[i]);
	}

	// Add the group shape to the list
	Addshape(groupShape);

	// Select the new group
	SetSelectedShape(groupShape);

	return true;
}

bool Graph::UnGroupShape(shape* groupShape)
{
	if (!groupShape) {
		return false;
	}
	
	if (!groupShape->IsGroup()) {

		return false;
	}


	// Get the shapes in the group using virtual methods
	int numShapes = groupShape->GetNumShapes();
	
	if (numShapes <= 0) {
		return false;
	}

	// Store the individual shapes before removing the group
	shape* individualShapes[10];
	int actualCount = 0;
	
	for (int i = 0; i < numShapes && actualCount < 10; i++) {
		shape* individualShape = groupShape->GetShape(i);
		if (individualShape) {
			individualShapes[actualCount] = individualShape;
			actualCount++;
		}
	}

	RemoveShape(groupShape);

	for (int i = 0; i < actualCount; i++) {
		if (individualShapes[i]) {
			Addshape(individualShapes[i]);
		}
	}

	return true;
}

void Graph::Undo() {
	if (undoTop >= 0) {
		
		redoStack[++redoTop] = CloneAllShapes();
		shapeCountForRedo[redoTop] = shapeCount;

		ClearShapes();
		shapeCount = shapeCountForUndo[undoTop];
		for (int i = 0; i < shapeCount; ++i) {
			shapesList[i] = undoStack[undoTop][i]->Clone();
		}

		--undoTop;
		SetSaved(false);
	}
}

void Graph::Redo() {
	if (redoTop >= 0) {
		
		undoStack[++undoTop] = CloneAllShapes();
		shapeCountForUndo[undoTop] = shapeCount;

		ClearShapes();
		shapeCount = shapeCountForRedo[redoTop];
		for (int i = 0; i < shapeCount; ++i) {
			shapesList[i] = redoStack[redoTop][i]->Clone();
		}

		--redoTop;
		SetSaved(false);
	}
}

