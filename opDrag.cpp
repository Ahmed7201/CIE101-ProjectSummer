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

    if (!selected)
    {
        pUI->PrintMessage("Please select a shape first.");
        return;
    }

    int startX, startY;
    pUI->GetPointClicked(startX, startY);
    pUI->PrintMessage("Click and hold to drag the shape...");

    // Wait until mouse button is pressed
    while (!pUI->IsMouseButtonDown())
    {
        // do nothing, just wait
    }

    // While dragging
    int currentX = startX, currentY = startY;
    while (pUI->IsMouseButtonDown())
    {
        int newX, newY;
        pUI->GetMouseCoord(newX, newY);

        // Only move if the cursor has changed position
        if (newX != currentX || newY != currentY)
        {
            int dx = newX - currentX;
            int dy = newY - currentY;
            selected->Move(dx, dy); // move by delta
            currentX = newX;
            currentY = newY;
            pControl->UpdateInterface(); // update drawing!
        }
    }

    pUI->PrintMessage("Shape released.");
}
