#include "opAddLine.h"
#include"Line.h"
#include"controller.h"
#include"GUI/GUI.h"

opAddLine::opAddLine(controller* pCont) : operation(pCont)
{}
opAddLine::~opAddLine()
{}
void opAddLine::Execute()
{
	Graph* pGraph = pControl->getGraph();
	pGraph->PushToUndo();
	Point Start_Point , End_Point;  // This point will be used to determine the radius of the circle
	GUI* pUI = pControl->GetUI();
	pUI->PrintMessage("New Line: Click at start point ");
	pUI->GetPointClicked(Start_Point.x, Start_Point.y);
	string msg = "Start Point is at (" + to_string(Start_Point.x) + ", " + to_string(Start_Point.y) + " )";
	msg += " ... Click at end point ";
	pUI->PrintMessage(msg);
	//Read 2nd corner and store in point P2
	pUI->GetPointClicked(End_Point.x, End_Point.y);
	

	pUI->ClearStatusBar();

	//Preapre all circle parameters
	GfxInfo LineGfxInfo;

	//get drawing, filling colors and pen width from the interface
	LineGfxInfo.DrawClr = pUI->getCrntDrawColor();
	LineGfxInfo.FillClr = pUI->getCrntFillColor();
	LineGfxInfo.BorderWdth = pUI->getCrntPenWidth();


	LineGfxInfo.isFilled = false;	//default is not filled
	LineGfxInfo.isSelected = false;	//defualt is not selected

	//Create a circle with the above parameters
	Line* L = new Line(Start_Point, End_Point, LineGfxInfo);

	//Get a pointer to the graph
	Graph* pGr = pControl->getGraph();

	//Add the circle to the list of shapes
	pGr->Addshape(L);


}

