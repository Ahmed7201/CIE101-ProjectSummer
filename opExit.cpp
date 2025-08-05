#include "opExit.h"
#include "controller.h"
#include "GUI/GUI.h"
#include "Shapes/Graph.h"
#include "opSave.h"

opExit::opExit(controller * pCont) : operation(pCont) {}

void opExit::Execute()
{
    GUI* pUI = pControl->GetUI();
    Graph* pGraph = pControl->getGraph();

    if (pGraph->IsSaved())
    {
        pUI->PrintMessage("Exiting... No unsaved changes.");
    }
    else
    {
        pUI->PrintMessage("You have unsaved changes. Save before exiting? (Y/N)");
        string userInput = pUI->GetSrting();

        if (userInput == "Y" || userInput == "y")
        {
            opSave saveOp(pControl);
            saveOp.Execute();
        }
        else if (userInput == "N" || userInput == "n")
        {
            pUI->PrintMessage("Exiting without saving.");
        }
        else
        {
            pUI->PrintMessage("Invalid input. Exit canceled.");
            return;
        }
    }

    exit(0);
}