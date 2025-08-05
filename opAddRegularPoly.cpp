#include "opAddRegularPoly.h"
#include "RegularPoly.h"
#include "controller.h"
#include "GUI/GUI.h"

opAddRegularPoly::opAddRegularPoly(controller* pCont) : operation(pCont)
{
}

opAddRegularPoly::~opAddRegularPoly()
{
}

void opAddRegularPoly::Execute()
{
    Point Center, Vertex;
    int NumSides;

    // Get a Pointer to the Input / Output Interfaces
    GUI* pUI = pControl->GetUI();

    // Step 1: Prompt for and get the center point
    pUI->PrintMessage("New Regular Polygon: Click at center");
    pUI->GetPointClicked(Center.x, Center.y);

    // Step 2: Prompt for and get one vertex point
    string msg = "Center is at (" + to_string(Center.x) + ", " + to_string(Center.y) + ")";
    msg += " ... Click at one vertex";
    pUI->PrintMessage(msg);
    pUI->GetPointClicked(Vertex.x, Vertex.y);

    // Step 3: Prompt for and get the number of sides
    pUI->PrintMessage("Enter number of sides (3 or more): ");
    string input = pUI->GetSrting(); // Note: Assuming GetSrting() is a typo for GetString()
    NumSides = 0;
    for (char c : input) {
        if (isdigit(c)) {
            NumSides = NumSides * 10 + (c - '0');
        }
    }
    // Validate number of sides
    if (NumSides < 3) {
        pUI->PrintMessage("Invalid: Number of sides must be 3 or more");
        return;
    }

    pUI->ClearStatusBar();

    // Prepare all Regular Polygon parameters
    GfxInfo PolyGfxInfo;

    // Get drawing, filling colors, and pen width from the interface
    PolyGfxInfo.DrawClr = pUI->getCrntDrawColor();
    PolyGfxInfo.FillClr = pUI->getCrntFillColor();
    PolyGfxInfo.BorderWdth = pUI->getCrntPenWidth();

    PolyGfxInfo.isFilled = true; // Default is filled, consistent with Circle, Square, etc.
    PolyGfxInfo.isSelected = false; // Default is not selected

    // Create a Regular Polygon with the above parameters
    RegularPoly* P = new RegularPoly(Center, Vertex, NumSides, PolyGfxInfo);

    // Get a pointer to the graph
    Graph* pGr = pControl->getGraph();

    // Add the Regular Polygon to the list of shapes
    pGr->Addshape(P);

    // Update the interface to display the new shape
    pControl->UpdateInterface();
}