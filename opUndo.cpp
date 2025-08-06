#include "opUndo.h"
#include "controller.h"
#include "shapes/Graph.h"
#include "GUI/GUI.h"

opUndo::opUndo(controller* pCont) : operation(pCont) {}

opUndo::~opUndo() {}

void opUndo::Execute() {
    
    Graph* pGraph = pControl->getGraph();
    GUI* pUI = pControl->GetUI();
    if (!pGraph) return;
    pGraph->Undo();
    pUI->PrintMessage("Undo performed.");
    pControl->UpdateInterface();
}
