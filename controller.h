#pragma once

#include "DEFS.h"
#include "Shapes\Graph.h"
#include "GUI\GUI.h"
#include "operations\Operation.h"
#include "Shapes\Graph.h"       
#include "Shapes\Shape.h"
//Ahmed
//push without commit
class operation; //forward declaration

//Main class that manages everything in the application.
class controller
{

	Graph* pGraph;	//pointe to the grapg
	GUI* pGUI;		//Pointer to UI class
	
	

public:	
	controller(); 
	~controller();
	
	// -- operation-Related Functions
	//Reads the input command from the user and returns the corresponding operation type
	operationType GetUseroperation() const;
	operation* createOperation(operationType) ; //Creates an operation
	void Run();
	
	operationType getCurrentMode() const;
	shape* getSelectedShape() const;

	Graph* getGraph() const;

	void setGraph(Graph* pG); //Set the current graph
	
	// -- Interface Management Functions
	GUI *GetUI() const; //Return pointer to the UI
	void UpdateInterface() const;	//Redraws all the drawing window
	

};

