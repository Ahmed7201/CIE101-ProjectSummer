#include "opDrag.h"
#include "controller.h"
#include "GUI/GUI.h"
#include "Shapes/shape.h"
#include "Shapes/Graph.h"
#include "windows.h"
opDrag::opDrag(controller* pCont) : operation(pCont) {}

void opDrag::Execute()
{
    GUI* pUI = pControl->GetUI();
    Graph* pGraph = pControl->getGraph();
    shape* selected = pGraph->GetSelectedShape();
    pGraph->PushToUndo();
    if (!selected)
    {
        pUI->PrintMessage("Please select a shape first.");
        return;
    }

    int startX, startY;
    pUI->GetPointClicked(startX, startY);
    pUI->PrintMessage("Click and hold to drag the shape...");

    while (!pUI->IsMouseButtonDown())
    {
    }

    int currentX = startX, currentY = startY;
    while (pUI->IsMouseButtonDown())
    {
        int newX, newY;
        pUI->GetMouseCoord(newX, newY);

        if (newX != currentX || newY != currentY)
        {
            int dx = newX - currentX;
            int dy = newY - currentY;
            selected->Move(dx, dy); 
            currentX = newX;
            currentY = newY;
            pControl->UpdateInterface(); 
        }
    }
    pUI->PrintMessage("Shape released.");
}
