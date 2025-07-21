#include "opAddCircle.h"
#include "Circle.h"
#include "controller.h"	
#include "GUI/GUI.h"	

opAddCircle::opAddCircle(controller* pCont) : operation(pCont)
{}
opAddCircle::~opAddCircle()
{}
//Execute the operation	
void opAddCircle::Execute()
{
	Point Center;
	Point Edge_Point; // This point will be used to determine the radius of the circle
	GUI* pUI = pControl->GetUI();
	pUI->PrintMessage("New Circle: Click at center");
	pUI->GetPointClicked(Center.x, Center.y);
	string msg = "Center is at (" + to_string(Center.x) + ", " + to_string(Center.y) + " )";
	pUI->PrintMessage("New Circle: Click at any point on circle ");
	pUI->GetPointClicked(Edge_Point.x, Edge_Point.y);
	
	

	pUI->ClearStatusBar();

	//Preapre all circle parameters
	GfxInfo CircGfxInfo;

	//get drawing, filling colors and pen width from the interface
	CircGfxInfo.DrawClr = pUI->getCrntDrawColor();
	CircGfxInfo.FillClr = pUI->getCrntFillColor();
	CircGfxInfo.BorderWdth = pUI->getCrntPenWidth();


	CircGfxInfo.isFilled = false;	//default is not filled
	CircGfxInfo.isSelected = false;	//defualt is not selected

	//Create a circle with the above parameters
	Circle* C = new Circle(Center,Edge_Point, CircGfxInfo);

	//Get a pointer to the graph
	Graph* pGr = pControl->getGraph();

	//Add the circle to the list of shapes
	pGr->Addshape(C);


}
