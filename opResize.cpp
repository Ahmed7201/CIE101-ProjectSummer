#include "opResize.h"
#include "controller.h"
#include "GUI/GUI.h"

opResize::opResize(controller* pCont) : operation(pCont)
{
}

opResize::~opResize()
{
}

void opResize::Execute()
{
    Graph* pGraph = pControl->getGraph();
    pGraph->PushToUndo();
    GUI* pUI = pControl->GetUI();

    // Get the currently selected shape
    shape* selectedShape = pGraph->GetSelectedShape();
    if (!selectedShape) {
        pUI->PrintMessage("No shape selected. Please select a shape first.");
        return;
    }

    // Ask user for scaling factor
    pUI->PrintMessage("Enter scaling factor (1/4, 1/2, 2, 4): ");
    string input = pUI->GetSrting();
    
    double scaleFactor = 1.0;
    bool validInput = false;
    
    // Parse the input
    if (input == "1/4" || input == "0.25") {
        scaleFactor = 0.25;
        validInput = true;
    }
    else if (input == "1/2" || input == "0.5") {
        scaleFactor = 0.5;
        validInput = true;
    }
    else if (input == "2") {
        scaleFactor = 2.0;
        validInput = true;
    }
    else if (input == "4") {
        scaleFactor = 4.0;
        validInput = true;
    }
    

    if (!validInput) {
        pUI->PrintMessage("Invalid scaling factor. Please enter 1/4, 1/2, 2, or 4.");
        return;
    }

    // Scale the selected shape
    selectedShape->Scale(scaleFactor);
    
    pUI->PrintMessage("Shape scaled by factor " + to_string(scaleFactor));
    pControl->UpdateInterface();
} 