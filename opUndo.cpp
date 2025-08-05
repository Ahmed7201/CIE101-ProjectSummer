#include "opUndo.h"
#include "controller.h"
#include "shapes/Graph.h"
#include "GUI/GUI.h"

opUndo::opUndo(controller* pCont) : operation(pCont) {}

void opUndo::Execute() {
    // Get the Graph from the controller
    Graph* pGraph = pControl->getGraph();
    GUI* pUI = pControl->GetUI();
    if (!pGraph) return;

    // Perform Undo
    pGraph->Undo();

    // Update GUI (if needed)
    pUI->PrintMessage("Undo performed.");
    pControl->UpdateInterface();
}
