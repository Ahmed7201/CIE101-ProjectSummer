#include "controller.h"
#include "operations\opAddRect.h"
#include "opAddSquare.h"
#include "opAddCircle.h"
#include "opAddLine.h"
#include"opAddTriangle.h"
#include "opAddOval.h"
#include "opSelect.h"
#include "opDrawColor.h"
#include "opFillColor.h"
#include "opColorPalete.h"
#include "opDelete.h"
#include "opRotate_90.h"

#include "opLoad.h"
//Constructor
controller::controller()
{
	pGraph = new Graph;
	pGUI = new GUI;	//Create GUI object
}

//==================================================================================//
//								operations-Related Functions							//
//==================================================================================//
operationType controller::GetUseroperation() const
{
	//Ask the input to get the operation from the user.
	return pGUI->GetUseroperation();		
}
////////////////////////////////////////////////////////////////////////////////////
//Creates an operation and executes it
operation* controller::createOperation(operationType OpType)
{
	operation* pOp = nullptr;

	
	//According to operation Type, create the corresponding operation object
	switch (OpType)
	{
		case DRAW_RECT:
			pOp = new opAddRect(this);
			break;
		case DRAW_CIRC:
			pOp = new opAddCircle(this);
			break;

		case DRAW_LINE:
			pOp = new opAddLine(this);

			break;

		case Draw_SQUARE:
			pOp = new opAddSquare(this);

			break;
		case DRAW_TRI:
			pOp = new opAddTriangle(this);

			break;
		case Draw_Oval:
			pOp = new opAddOval(this);
			break;
		case Select:
			pOp = new opSelect(this);
			break;
		case LOAD:
			pOp = new opLoad(this, "shapes.txt"); 
			break;
		case Delete:
			pOp = new opDelete(this);
			break;
		case ROTATE:
			pOp = new opRotate_90(this);
			break;

		case CHNG_DRAW_CLR:
			pOp = new opDrawColor(this);
			break;
		case CHNG_FILL_CLR:
			pOp = new opFillColor(this);
			break;
		case Draw_Color_Palette:
			pOp = new opColorPalete(this);
			break;

		case EXIT:
			///create Exitoperation here
			
			break;
		
		case STATUS:	//a click on the status bar ==> no operation
			break;
	}

	return pOp;
	
}
//==================================================================================//
//							Interface Management Functions							//
//==================================================================================//

//Draw all shapes on the user interface
void controller::UpdateInterface() const
{	
	pGraph->Draw(pGUI);
}
////////////////////////////////////////////////////////////////////////////////////
//Return a pointer to the UI
GUI *controller::GetUI() const
{	return pGUI; }
////////////////////////////////////////////////////////////////////////////////////
//Return a pointer to the Graph
Graph* controller::getGraph() const
{
	return pGraph;
}



//Destructor
controller::~controller()
{
	delete pGUI;
	delete pGraph;
	
}



//==================================================================================//
//							Run function											//
//==================================================================================//
void controller::Run()
{
	operationType OpType;
	do
	{
		//1. Ask the GUI to read the required operation from the user
		OpType = GetUseroperation();

		//2. Create an operation coresspondingly
		operation* pOpr = createOperation(OpType);
		 
		//3. Execute the created operation
		if (pOpr)
		{
			pOpr->Execute();//Execute
			delete pOpr;	//operation is not needed any more ==> delete it
			pOpr = nullptr;
		}

		//Update the interface
		UpdateInterface();

	} while (OpType != EXIT);

}