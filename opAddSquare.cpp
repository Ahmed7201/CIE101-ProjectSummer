#include "opAddSquare.h"
#include "Square.h"
#include "controller.h"	
#include "GUI/GUI.h"

opAddSquare::opAddSquare(controller* pCont) : operation(pCont)
{
}
opAddSquare::~opAddSquare()
{
}
//Execute the operation	
void opAddSquare::Execute()
{
	Point P1,P2;
	GUI* pUI = pControl->GetUI();
	pUI->PrintMessage("New Square: Click at center");
	pUI->GetPointClicked(P1.x, P1.y);
	string msg = "Center is at (" + to_string(P1.x) + ", " + to_string(P1.y) + " )";

	pUI->ClearStatusBar();

	//Preapre all Square parameters
	GfxInfo SquareGfxInfo;

	//get drawing, filling colors and pen width from the interface
	SquareGfxInfo.DrawClr = pUI->getCrntDrawColor();
	SquareGfxInfo.FillClr = pUI->getCrntFillColor();
	SquareGfxInfo.BorderWdth = pUI->getCrntPenWidth();


	SquareGfxInfo.isFilled = false;	//default is not filled
	SquareGfxInfo.isSelected = false;	//defualt is not selected

	//Create a Square with the above parameters
	Square* C = new Square(P1,P2, SquareGfxInfo);

	//Get a pointer to the graph
	Graph* pGr = pControl->getGraph();

	//Add the Square to the list of shapes
	pGr->Addshape(C);


}