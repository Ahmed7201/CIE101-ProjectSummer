#include "opColorPalete.h"
#include "controller.h"
#include "GUI/GUI.h"


opColorPalete::opColorPalete(controller* pCont) : operation(pCont)
{
}
opColorPalete::~opColorPalete()
{
	// Destructor
}
void opColorPalete::Execute()
{
	GUI* pUI = pControl->GetUI();
	pUI->DrawColorPalette(); // Draw the color palette
	color selectedColor = pUI->CreateColorPalette(); // Get the selected color from the palette
	pUI->SetDrawColor(selectedColor); // Set the selected color as the drawing color
	pUI->ClearStatusBar(); // Clear the status bar after selection
}
