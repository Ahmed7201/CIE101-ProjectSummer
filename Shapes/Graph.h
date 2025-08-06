#pragma once
#include "Shape.h"
#include <fstream>

using namespace std;

//forward decl
class GUI;	

//A class that is responsible on everything related to shapes
class Graph
{
	enum { maxShapeCount = 1000 };
private:
	shape* shapesList[maxShapeCount]; //a container to hold all shapes							   
	int shapeCount;			// Actual number of shapes stored in the list
	shape* selectedShape;	//pointer to the currently selected shape
	bool isSaved;
	static const int maxUndoRedo = 20; // Or any limit you want
	shape** undoStack[maxUndoRedo];
	shape** redoStack[maxUndoRedo];
	int shapeCountForUndo[maxUndoRedo];  // Add this
	int shapeCountForRedo[maxUndoRedo];  // Add this
	int undoTop = -1;
	int redoTop = -1;

public:										
	
	Graph();
	~Graph();
	void Addshape(shape* pFig); //Adds a new shape to the shapesList
	void Draw(GUI* pUI) const;			//Draw the graph (draw all shapes)
	shape* Getshape(int x, int y) const; //Search for a shape given a point inside the shape
	void UnselectAllShapes(GUI* pUI); // Added to manage selection
	shape* GetSelectedShape() const; // Get the currently selected shape
	void SetSelectedShape(shape* shape); // Added to set the selected shape
	void CopySelectedShape(shape* pShape); // Copy the selected shape
	void Save(ofstream& outfile);	//Save all shapes to a file
	void load(ifstream& inputfile);	//Load all shapes from a file
	void RemoveShape(shape* pShape); //Delete shpaes
	void RotateSelectedShape(shape* pShape); // Rotate the selected shape by a given angle
	void PasteCopiedShape(Point P1);
	bool IsSaved() const;
	void SetSaved(bool);
	void SendToBack(shape* pShape);
	void PushToUndoStack();
	void PushToUndo();
	shape** CloneAllShapes();
	void Undo();
	void Redo();
	void ClearShapes();
	
	// Group-related methods
	int GetSelectedShapesCount() const;  // Count how many shapes are selected
	shape* GetSelectedShape(int index) const;  // Get selected shape at index
	bool GroupSelectedShapes();  // Group all selected shapes
	bool UnGroupShape(shape* groupShape);  // Ungroup a shape group
};
