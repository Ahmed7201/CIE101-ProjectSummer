#include "opSelect.h"
#include "controller.h"
#include "GUI/GUI.h"
//Abdallah

opSelect::opSelect(controller* pCont) : operation(pCont) {}

opSelect::~opSelect() {}

void opSelect::Execute() {
    Point clickedPoint;
    GUI* pUI = pControl->GetUI();
    Graph* pGraph = pControl->getGraph();

    // Get the point clicked by the user
    pUI->GetPointClicked(clickedPoint.x, clickedPoint.y);

    // Get the shape at the clicked point
    shape* clickedShape = pGraph->Getshape(clickedPoint.x, clickedPoint.y);


    if (clickedShape) {
        // Check if the shape is already selected
        bool isCurrentlySelected = clickedShape->IsSelected();
        if (isCurrentlySelected) {
            // Unselect the shape
            clickedShape->SetSelected(false);
            pGraph->SetSelectedShape(nullptr);
			GfxInfo gfxInfo = clickedShape->GetGfxInfo();
			gfxInfo.DrawClr = pUI->getCrntDrawColor(); // Reset to original color
			clickedShape->SetGfxInfo(gfxInfo); // Update GfxInfo
          
            pUI->PrintMessage("Shape unselected");
        }
        else {
            // Unselect any previously selected shape
            pGraph->UnselectAllShapes(pUI);
            // Select the new shape
            clickedShape->SetSelected(true);
            pGraph->SetSelectedShape(clickedShape) ;
            // Highlight the shape
            GfxInfo gfxInfo = clickedShape->GetGfxInfo();
            color originalColor = gfxInfo.DrawClr; // Store original color
            gfxInfo.DrawClr = pUI->GetHighlightColor(); // Apply highlight
            clickedShape->SetGfxInfo(gfxInfo); // Update GfxInfo
           
            // Display shape info
            string info = "Selected: " + clickedShape->GetShapeType() +
                " at (" + to_string(clickedPoint.x) + "," + to_string(clickedPoint.y) +
                ") Color: (" + to_string(originalColor.ucRed) + "," +
                to_string(originalColor.ucGreen) + "," + to_string(originalColor.ucBlue) + ")";
            pUI->PrintMessage(info);
        }
    }
    else {
        // No shape found, unselect all
        pGraph->UnselectAllShapes(pUI);
        pUI->PrintMessage("No shape found, all shapes unselected");
    }
	pControl->UpdateInterface(); // Refresh the interface to reflect changes
}