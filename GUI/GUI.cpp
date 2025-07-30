#include "GUI.h"
#include "../operations/operation.h"
#include "..//controller.h"
#include <algorithm>

GUI::GUI()
{

	width = 1300;
	height = 700;
	wx = 5;
	wy = 5;

	
	StatusBarHeight = 50;
	StatusBarWidth = 0;
	ToolBarHeight = 50;
	MenuIconWidth = 30;

	DrawColor = DARKGREEN;	//default Drawing color
	FillColor = YELLOW;	//default Filling color
	MsgColor = BLUE;		//Messages color
	BkGrndColor = WHITE;	//Background color
	HighlightColor = MAGENTA;	//This color should NOT be used to draw shapes. use it for highlight only
	StatusBarColor = LIGHTSEAGREEN;
	PenWidth = 3;	//default width of the shapes frames
	



	//Create the output window
	pWind = CreateWind(width, height, wx, wy);
	//Change the title
	pWind->ChangeTitle("- - - - - - - - - - ^ ZAG Shape_Studio ZAG ^ - - - - - - - - - -");
	CreateDrawToolBar();
	CreateStatusBar();
	
	
}




//======================================================================================//
//								Input Functions										//
//======================================================================================//
void GUI::GetPointClicked(int& x, int& y) const
{
	pWind->WaitMouseClick(x, y);	//Wait for mouse click
}

string GUI::GetSrting() const
{
	string Label;
	char Key;
	keytype ktype;
	pWind->FlushKeyQueue();
	while (1)
	{
		ktype = pWind->WaitKeyPress(Key);
		if (ktype == ESCAPE )	//ESCAPE key is pressed
			return "";	//returns nothing as user has cancelled label
		if (Key == 13)	//ENTER key is pressed
			return Label;
		if (Key == 8)	//BackSpace is pressed
			if( Label.size() > 0)	
				Label.resize(Label.size() - 1);
			else
				Key = '\0';		
		else
			Label += Key;
		PrintMessage(Label);
	}
}

//This function reads the position where the user clicks to determine the desired operation
operationType GUI::GetUseroperation() const
{
	int x, y;
	pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click

	//[1] If user clicks on the Toolbar
	if (y >= 0 && y < ToolBarHeight)
	{
		//Check whick Menu icon was clicked
		//==> This assumes that menu icons are lined up horizontally <==
		int ClickedIconOrder = (x / MenuIconWidth);
		//Divide x coord of the point clicked by the menu icon width (int division)
		//if division result is 0 ==> first icon is clicked, if 1 ==> 2nd icon and so on

		switch (ClickedIconOrder)
		{
		case ICON_RECT: return DRAW_RECT;
		case ICON_TRI: return DRAW_TRI;
		case ICON_LINE: return DRAW_LINE;
		case ICON_CIRC: return DRAW_CIRC;
		case ICON_SQUARE: return Draw_SQUARE;
		case ICON_OVAL: return Draw_Oval;
		case ICON_REG_POLYGON: return Draw_Regular_Polygon;
		case ICON_DRAW_CLR: return CHNG_DRAW_CLR;
		case ICON_FILL_CLR: return CHNG_FILL_CLR;


		case ICON_Select: return Select;
		case ICON_EXIT: return EXIT;
        
		default: return EMPTY;	//A click on empty place in desgin toolbar
		}
	}

	//[2] User clicks on the drawing area
	if (y >= ToolBarHeight && y < height - StatusBarHeight)
	{
		return DRAWING_AREA;
	}

	//[3] User clicks on the status bar
	return STATUS;
	

}
////////////////////////////////////////////////////



//======================================================================================//
//								Output Functions										//
//======================================================================================//

window* GUI::CreateWind(int w, int h, int x, int y) const
{
	window* pW = new window(w, h, x, y);
	pW->SetBrush(BkGrndColor);
	pW->SetPen(BkGrndColor, 1);
	pW->DrawRectangle(0, ToolBarHeight, w, h);

	return pW;
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::CreateStatusBar() const
{
	pWind->SetPen(StatusBarColor, 1);
	pWind->SetBrush(StatusBarColor);
	pWind->DrawRectangle(0, height - StatusBarHeight, width, height);


}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::ClearStatusBar() const
{
	//Clear Status bar by drawing a filled white rectangle
	pWind->SetPen(StatusBarColor, 1);
	pWind->SetBrush(StatusBarColor);
	pWind->DrawRectangle(0, height - StatusBarHeight, width, height);
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::CreateDrawToolBar() 
{

	//You can draw the tool bar icons in any way you want.
	//Below is one possible way

	//First prepare List of images for each menu icon
	//To control the order of these images in the menu, 
	//reoder them in UI_Info.h ==> enum DrawMenuIcon
	string MenuIconImages[DRAW_ICON_COUNT];
	MenuIconImages[ICON_RECT] = "images\\MenuIcons\\Menu_Rect.jpg";
	MenuIconImages[ICON_TRI] = "images\\MenuIcons\\Menu_Tri.jpg";
	MenuIconImages[ICON_CIRC] = "images\\MenuIcons\\Menu_Circ.jpg";
	MenuIconImages[ICON_SQUARE] = "images\\MenuIcons\\Menu_Square.jpg";
	MenuIconImages[ICON_EXIT] = "images\\MenuIcons\\Menu_Exit.jpg";
	MenuIconImages[ICON_LINE] = "images\\MenuIcons\\Menu_Line.jpg";
	MenuIconImages[ICON_OVAL] = "images\\MenuIcons\\Menu_Oval.jpg";
	MenuIconImages[ICON_REG_POLYGON] = "images\\MenuIcons\\Menu_RegPolygon.jpg";
	MenuIconImages[ICON_DRAW_CLR] = "images\\MenuIcons\\Menu_Pen.jpg";
	MenuIconImages[ICON_FILL_CLR] = "images\\MenuIcons\\Menu_Fill.jpg";



	MenuIconImages[ICON_Select] = "images\\MenuIcons\\Menu_Select.jpg";
	


	//TODO: Prepare images for each menu icon and add it to the list

	//Draw menu icon one image at a time
	for (int i = 0; i < DRAW_ICON_COUNT; i++)
		pWind->DrawImage(MenuIconImages[i], i * MenuIconWidth, 0, MenuIconWidth, ToolBarHeight);



	//Draw a line under the toolbar
	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, ToolBarHeight, width, ToolBarHeight);

}


void GUI::DrawColorPalette()
{
	pWind->SetPen(BLACK, 1);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(StatusBarWidth, height - StatusBarHeight, StatusBarWidth + 108, height, FILLED);
	pWind->SetBrush(BLACK);
	pWind->DrawRectangle(StatusBarWidth + 108, height - StatusBarHeight, StatusBarWidth + 216, height, FILLED);
	pWind->SetBrush(GREEN);
	pWind->DrawRectangle(StatusBarWidth + 216, height - StatusBarHeight, StatusBarWidth + 324, height, FILLED);
	pWind->SetBrush(BLUE);
	pWind->DrawRectangle(StatusBarWidth + 324, height - StatusBarHeight, StatusBarWidth + 432, height, FILLED);
	pWind->SetBrush(YELLOW);
	pWind->DrawRectangle(StatusBarWidth + 432, height - StatusBarHeight, StatusBarWidth + 540, height, FILLED);
	pWind->SetBrush(RED);
	pWind->DrawRectangle(StatusBarWidth + 540, height - StatusBarHeight, StatusBarWidth + 648, height, FILLED);
	pWind->SetBrush(DARKGREEN);
	pWind->DrawRectangle(StatusBarWidth + 648, height - StatusBarHeight, StatusBarWidth + 756, height, FILLED);
	pWind->SetBrush(MAGENTA);
	pWind->DrawRectangle(StatusBarWidth + 756, height - StatusBarHeight, StatusBarWidth + 864, height, FILLED);
	pWind->SetBrush(CYAN);
	pWind->DrawRectangle(StatusBarWidth + 864, height - StatusBarHeight, StatusBarWidth + 972, height, FILLED);
	pWind->SetBrush(ORANGE);
	pWind->DrawRectangle(StatusBarWidth + 972, height - StatusBarHeight, StatusBarWidth + 1080, height, FILLED);
	pWind->SetBrush(PURPLE);
	pWind->DrawRectangle(StatusBarWidth + 1080, height - StatusBarHeight, StatusBarWidth + 1188, height, FILLED);
	pWind->SetBrush(GRAY);
	pWind->DrawRectangle(StatusBarWidth + 1188, height - StatusBarHeight, width, height, FILLED);
	
}

color GUI::CreateColorPalette()
{
    color CLR;
    int x, y;
    DrawColorPalette();
    pWind->WaitMouseClick(x, y);
    if ((y > height - StatusBarHeight) && (y < height))
    {
        if ((x >= StatusBarWidth) && (x < StatusBarWidth + 108))
        {
			CLR = WHITE;
        }
        else if ((x >= StatusBarWidth + 108) && (x < StatusBarWidth + 216))
        {
            CLR = BLACK;
        }
        else if ((x >= StatusBarWidth + 216) && (x < StatusBarWidth + 324))
        {
            CLR = GREEN;
        }
        else if ((x >= StatusBarWidth + 324) && (x < StatusBarWidth + 432))
        {
            CLR = BLUE;
        }
        else if ((x >= StatusBarWidth + 432) && (x < StatusBarWidth + 540))
        {
            CLR = YELLOW;
        }
        else if ((x >= StatusBarWidth + 540) && (x < StatusBarWidth + 648))
        {
            CLR = RED;
        }
        else if ((x >= StatusBarWidth + 648) && (x < StatusBarWidth + 756))
        {
            CLR = DARKGREEN;
        }
        else if ((x >= StatusBarWidth + 756) && (x < StatusBarWidth + 864))
        {
            CLR = MAGENTA;
        }
        else if ((x >= StatusBarWidth + 864) && (x < StatusBarWidth + 972))
        {
            CLR = CYAN;
        }
        else if ((x >= StatusBarWidth + 972) && (x < StatusBarWidth + 1080))
        {
            CLR = ORANGE;
        }
        else if ((x >= StatusBarWidth + 1080) && (x < StatusBarWidth + 1188))
        {
            CLR = PURPLE;
        }
        else if ((x >= StatusBarWidth + 1188) && (x < width))
        {
            CLR = GRAY;
        }
    }
    ClearStatusBar();
    return CLR;
}




//////////////////////////////////////////////////////////////////////////////////////////

void GUI::ClearDrawArea() const
{
	pWind->SetPen(BkGrndColor, 1);
	pWind->SetBrush(BkGrndColor);
	pWind->DrawRectangle(0, ToolBarHeight, width, height - StatusBarHeight);

}
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::PrintMessage(string msg) const	//Prints a message on status bar
{
	ClearStatusBar();	//First clear the status bar

	pWind->SetPen(MsgColor, 50);
	pWind->SetFont(24, BOLD, BY_NAME, "Arial");
	pWind->DrawString(10, height - (int)(0.75 * StatusBarHeight), msg);
}
//////////////////////////////////////////////////////////////////////////////////////////

color GUI::getCrntDrawColor() const //get current drwawing color
{
	return DrawColor;
}
//////////////////////////////////////////////////////////////////////////////////////////

color GUI::getCrntFillColor() const	//get current filling color
{
	return FillColor;
}
//////////////////////////////////////////////////////////////////////////////////////////

int GUI::getCrntPenWidth() const		//get current pen width
{
	return PenWidth;
}

//======================================================================================//
//								shapes Drawing Functions								//
//======================================================================================//
void GUI::DrawLine(Point P1, Point P2, GfxInfo LineGfxInfo) const
{
	color DrawingClr;
	if (LineGfxInfo.isSelected)	//shape is selected
		DrawingClr = HighlightColor; //shape should be drawn highlighted
	else
		DrawingClr = LineGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, LineGfxInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (LineGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(LineGfxInfo.FillClr);
	}
	else
		style = FRAME;

	pWind->DrawLine(P1.x, P1.y, P2.x, P2.y, style);

}

void GUI::DrawTriangle(Point P1, Point P2, Point P3, GfxInfo TriGfxInfo) const
{
	color DrawingClr;
	if (TriGfxInfo.isSelected) // shape is selected
		DrawingClr = HighlightColor; // shape should be drawn highlighted
	else
		DrawingClr = TriGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, TriGfxInfo.BorderWdth); // Set Drawing color & width

	drawstyle style;
	if (TriGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(TriGfxInfo.FillClr);
	}
	else
		style = FRAME;

	pWind->DrawTriangle(P1.x, P1.y, P2.x, P2.y, P3.x, P3.y, style);
}

void GUI::DrawCircle(Point Center, double Radius, GfxInfo CircGfxInfo) const
{
	color DrawingClr;
	if (CircGfxInfo.isSelected)	//shape is selected
		DrawingClr = HighlightColor; //shape should be drawn highlighted
	else
		DrawingClr = CircGfxInfo.DrawClr;
	pWind->SetPen(DrawingClr, CircGfxInfo.BorderWdth);	//Set Drawing color & width
	drawstyle style;
	if (CircGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(CircGfxInfo.FillClr);
	}
	else
		style = FRAME;
	pWind->DrawCircle(Center.x, Center.y, Radius, style);
}

void GUI::DrawRect(Point P1, Point P2, GfxInfo RectGfxInfo) const
{
	color DrawingClr;
	if (RectGfxInfo.isSelected)	//shape is selected
		DrawingClr = HighlightColor; //shape should be drawn highlighted
	else
		DrawingClr = RectGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, RectGfxInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (RectGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(RectGfxInfo.FillClr);
	}
	else
		style = FRAME;

	pWind->DrawRectangle(P1.x, P1.y, P2.x, P2.y, style);

}


void GUI::DrawSquare(Point P1, Point P2, GfxInfo SquareGfxInfo) const
{
	color DrawingClr;
	if (SquareGfxInfo.isSelected)	//shape is selected
		DrawingClr = HighlightColor; //shape should be drawn highlighted
	else
		DrawingClr = SquareGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, SquareGfxInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (SquareGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(SquareGfxInfo.FillClr);
	}
	else 
		style = FRAME;

	int side = (abs(P2.x - P1.x), abs(P2.y - P1.y));
	pWind->DrawSquare(P1.x, P1.y, side, style);


}
color GUI::getHighlightColor()const
{
	return HighlightColor;
}




void GUI::SetDrawColor(color newColor)
{
	DrawColor = newColor;
}
void GUI::SetFillColor(color newColor)
{
	FillColor = newColor;
}

//////////////////////////////////////////////////////////////////////////////////////////
GUI::~GUI()
{
	delete pWind;
}

