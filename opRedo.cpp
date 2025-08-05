#include "opRedo.h"
#include "controller.h"
#include "shapes/Graph.h"
#include "GUI/GUI.h"

opRedo::opRedo(controller* pCont) : operation(pCont) {}

opRedo::~opRedo() {}

void opRedo::Execute() {
    // Get the Graph from the controller
    Graph* pGraph = pControl->getGraph();
    GUI* pUI = pControl->GetUI();
    if (!pGraph) return;

    // Perform Redo
    pGraph->Redo();

    // Update GUI (if needed)
    pUI->PrintMessage("Redo performed.");
    pControl->UpdateInterface();
}
