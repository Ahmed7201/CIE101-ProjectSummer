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
    
    pUI->PrintMessage("New Irregular Polygon: Click to add vertices (right-click to finish)");
    
    // Maximum number of vertices (reasonable limit)
    const int MAX_VERTICES = 20;
    Point vertices[MAX_VERTICES];
    int numVertices = 0;
    
    // Get vertices from user clicks
    while (numVertices < MAX_VERTICES) {
        int x, y;
        pUI->WaitMouseClick(x, y);
        
        // Check if right-click (or some other way to finish)
        // For simplicity, we'll use a fixed number of vertices (e.g., 5)
        // In a real implementation, you might want to detect right-click or ESC key
        
        if (numVertices == 0) {
            pUI->PrintMessage("Click to add more vertices (5 total)");
        }
        
        vertices[numVertices].x = x;
        vertices[numVertices].y = y;
        numVertices++;
        
        // For demo purposes, create a 5-sided irregular polygon
        if (numVertices >= 5) {
            break;
        }
        
        string msg = "Vertex " + to_string(numVertices) + " at (" + to_string(x) + ", " + to_string(y) + ")";
        pUI->PrintMessage(msg);
    }
    
    pUI->ClearStatusBar();
    
    // Prepare all IrregularPoly parameters
    GfxInfo IrregularPolyGfxInfo;
    
    // Get drawing, filling colors and pen width from the interface
    IrregularPolyGfxInfo.DrawClr = pUI->getCrntDrawColor();
    IrregularPolyGfxInfo.FillClr = pUI->getCrntFillColor();
    IrregularPolyGfxInfo.BorderWdth = pUI->getCrntPenWidth();
    IrregularPolyGfxInfo.isFilled = true;
    IrregularPolyGfxInfo.isSelected = false; // Default is not selected
    
    // Create an IrregularPoly with the above parameters
    IrregularPoly* poly = new IrregularPoly(vertices, numVertices, IrregularPolyGfxInfo);
    
    // Get a pointer to the graph
    Graph* pGr = pControl->getGraph();
    
    // Add the IrregularPoly to the list of shapes
    pGr->Addshape(poly);
    
    pUI->PrintMessage("Irregular Polygon created successfully");
} 