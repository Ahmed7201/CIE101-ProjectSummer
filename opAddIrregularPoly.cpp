#include "opAddIrregularPoly.h"
#include "IrregularPoly.h"
#include "controller.h"
#include "GUI/GUI.h"

opAddIrregularPoly::opAddIrregularPoly(controller* pCont) : operation(pCont)
{
}

opAddIrregularPoly::~opAddIrregularPoly()
{
}

void opAddIrregularPoly::Execute()
{
    Graph* pGraph = pControl->getGraph();
    pGraph->PushToUndo();
    GUI* pUI = pControl->GetUI();
    
    // Step 1: Ask user for number of vertices
    pUI->PrintMessage("Enter number of vertices (3-20): ");
    string input = pUI->GetSrting();
    
    // Parse the input to get number of vertices
    int numVertices = 0;
    for (char c : input) {
        if (isdigit(c)) {
            numVertices = numVertices * 10 + (c - '0');
        }
    }
    
    // Validate number of vertices
    if (numVertices < 3 || numVertices > 20) {
        pUI->PrintMessage("Invalid: Number of vertices must be between 3 and 20");
        return;
    }
    
    // Step 2: Collect vertices from user clicks
    Point* vertices = new Point[numVertices];
    
    pUI->PrintMessage("Click to place " + to_string(numVertices) + " vertices");
    
    for (int i = 0; i < numVertices; i++) {
        int x, y;
        pUI->GetPointClicked(x, y);
        
        vertices[i].x = x;
        vertices[i].y = y;
        
        string msg = "Vertex " + to_string(i + 1) + " at (" + to_string(x) + ", " + to_string(y) + ")";
        if (i < numVertices - 1) {
            msg += " - Click for next vertex";
        }
        pUI->PrintMessage(msg);
    }
    
    pUI->ClearStatusBar();
    
    // Step 3: Prepare graphics info
    GfxInfo IrregularPolyGfxInfo;
    
    // Get drawing, filling colors and pen width from the interface
    IrregularPolyGfxInfo.DrawClr = pUI->getCrntDrawColor();
    IrregularPolyGfxInfo.FillClr = pUI->getCrntFillColor();
    IrregularPolyGfxInfo.BorderWdth = pUI->getCrntPenWidth();
    IrregularPolyGfxInfo.isFilled = true;
    IrregularPolyGfxInfo.isSelected = false;
    
    // Step 4: Create the irregular polygon
    IrregularPoly* poly = new IrregularPoly(vertices, numVertices, IrregularPolyGfxInfo);
    
    // Step 5: Add to graph
    Graph* pGr = pControl->getGraph();
    pGr->Addshape(poly);
    
    // Clean up
    delete[] vertices;
    
    pUI->PrintMessage("Irregular Polygon created successfully with " + to_string(numVertices) + " vertices");
}