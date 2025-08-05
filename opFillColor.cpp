#include "opFillColor.h"
#include "controller.h"
#include "GUI/GUI.h"

opFillColor::opFillColor(controller* pCont) : operation(pCont) {}

opFillColor::~opFillColor() {}

void opFillColor::Execute()
{
    GUI* pUI = pControl->GetUI();
    color selectedColor = pUI->CreateColorPalette();
    pUI->SetFillColor(selectedColor);
}