#include "opPaste.h"
#include "controller.h"
#include "Shapes/Graph.h"

opPaste::opPaste(controller* pCont) : operation(pCont) {}

void opPaste::Execute() {
    Graph* pGraph = pControl->getGraph();
    pGraph->PasteCopiedShape();
}
