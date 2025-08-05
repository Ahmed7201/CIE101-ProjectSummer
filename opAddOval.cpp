#include "opAddOval.h"
#include "Oval.h"
#include "controller.h"	
#include "GUI/GUI.h"	

opAddOval::opAddOval(controller* pCont) : operation(pCont)
{}
opAddOval::~opAddOval()
{}
//Execute the operation	
void opAddOval::Execute()
{
	Graph* pGraph = pControl->getGraph();
	pGraph->PushToUndo();
	Point Center;
	Point Edge_Point; // This point will be used to determine the radius of the Oval
	GUI* pUI = pControl->GetUI();
	pUI->PrintMessage("New Oval: Click at center");
	pUI->GetPointClicked(Center.x, Center.y);
	
	string msg = "Center is at (" + to_string(Center.x) + ", " + to_string(Center.y) + " )";
	pUI->PrintMessage("New Oval: Click at any point on Oval ");
	pUI->GetPointClicked(Edge_Point.x, Edge_Point.y);
	
	

	pUI->ClearStatusBar();

	//Preapre all Oval parameters
	GfxInfo OvalGfxInfo;

	//get drawing, filling colors and pen width from the interface
	OvalGfxInfo.DrawClr = pUI->getCrntDrawColor();
	OvalGfxInfo.FillClr = pUI->getCrntFillColor();
	OvalGfxInfo.BorderWdth = pUI->getCrntPenWidth();


	OvalGfxInfo.isFilled = true;	//default is not filled
	OvalGfxInfo.isSelected = false;	//defualt is not selected

	//Create a Oval with the above parameters
	Oval * O = new Oval(Center,Edge_Point, OvalGfxInfo);

	//Get a pointer to the graph
	Graph* pGr = pControl->getGraph();

	//Add the Oval to the list of shapes
	pGr->Addshape(O);


}

