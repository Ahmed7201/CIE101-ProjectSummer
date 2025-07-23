#include "opDrawColor.h"
#include "controller.h"	
#include "GUI/GUI.h"


opDrawColor::opDrawColor(controller* pCont) : operation(pCont) {}

void opDrawColor::Execute()
{
    GUI* pUI = pControl->GetUI();
    color selectedColor = pUI->CreateColorPalette();
    pUI->SetDrawColor(selectedColor);  // Apply general pen color change
}
