#include "opAddCircle.h"
#include "controller.h"	
#include "GUI/GUI.h"	

opAddCircle::opAddCircle(controller* pCont) : operation(pCont)
{}
opAddCircle::~opAddCircle()
{}
//Execute the operation	
void opAddCircle::Execute()
{
	Point P1;
	GUI* pUI = pControl->GetUI();
	pUI->PrintMessage("New Circle: Click at center");
	pUI->GetPointClicked(P1.x, P1.y);
	string msg = "Center is at (" + to_string(P1.x) + ", " + to_string(P1.y) + " )";

	pUI->ClearStatusBar();

	//Preapre all rectangle parameters
	GfxInfo RectGfxInfo;

	//get drawing, filling colors and pen width from the interface
	RectGfxInfo.DrawClr = pUI->getCrntDrawColor();
	RectGfxInfo.FillClr = pUI->getCrntFillColor();
	RectGfxInfo.BorderWdth = pUI->getCrntPenWidth();


	RectGfxInfo.isFilled = false;	//default is not filled
	RectGfxInfo.isSelected = false;	//defualt is not selected

	//Create a circle with the above parameters
	Circle* C = new Circle(P1, RectGfxInfo);

	//Get a pointer to the graph
	Graph* pGr = pControl->getGraph();

	//Add the rectangle to the list of shapes
	pGr->Addshape(C);


}
