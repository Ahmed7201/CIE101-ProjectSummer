#include "opAddTriangle.h"
#include "Triangle.h"
#include "controller.h"
#include "GUI/GUI.h"

opAddTriangle::opAddTriangle(controller* pCont) : operation(pCont)
{
}
opAddTriangle::~opAddTriangle()
{
}
//Execute the operation
void opAddTriangle::Execute()
{
	    Graph* pGraph = pControl->getGraph();
    pGraph->PushToUndo();
	Point P1, P2, P3;

	//Get a Pointer to the Input / Output Interfaces
	GUI* pUI = pControl->GetUI();

	pUI->PrintMessage("New Triangle: Click at first corner");
	//Read 1st corner and store in point P1
	pUI->GetPointClicked(P1.x, P1.y);

	string msg = "First corner is at (" + to_string(P1.x) + ", " + to_string(P1.y) + " )";
	msg += " ... Click at second corner";
	pUI->PrintMessage(msg);
	//Read 2nd corner and store in point P2
	pUI->GetPointClicked(P2.x, P2.y);
	pUI->ClearStatusBar();
	//Read 3nd corner and store in point P3
	msg += " is at (" + to_string(P2.x) + ", " + to_string(P2.y) +") " "... Click at Third corner";
	pUI->PrintMessage(msg);
	pUI->GetPointClicked(P3.x, P3.y);
	pUI->ClearStatusBar();

	//Preapre all Triangle parameters
	GfxInfo TriangleGfxInfo;

	//get drawing, filling colors and pen width from the interface
	TriangleGfxInfo.DrawClr = pUI->getCrntDrawColor();
	TriangleGfxInfo.FillClr = pUI->getCrntFillColor();
	TriangleGfxInfo.BorderWdth = pUI->getCrntPenWidth();


	TriangleGfxInfo.isFilled = true; //default is not filled
	TriangleGfxInfo.isSelected = false; //defualt is not selected


	//Create a Triangle with the above parameters
	Triangle* T = new Triangle(P1, P2, P3, TriangleGfxInfo);

	//Get a pointer to the graph
	Graph* pGr = pControl->getGraph();

	//Add the Triangle to the list of shapes
	pGr->Addshape(T);

}