#pragma once

#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\Defs.h"

#include <string>
using namespace std;

struct Point	//To be used for shapes points
{
	int x, y;
};

struct GfxInfo	//Graphical info common for all shapes (you may add more members)
{
	color DrawClr;	//Draw color of the shape
	color FillClr;	//Fill color of the shape
	bool isFilled;	//shape Filled or not
	int BorderWdth;	//Width of shape borders
	bool isSelected;	//true if the shape is selected.
};




class GUI
{
	enum MenuIcon //The icons of the menu (you should add more icons)
	{
		//Note: Icons are ordered here as they appear in menu
		//If you want to change the menu icons order, change the order here
		ICON_RECT,		//Recangle icon in menu
		ICON_TRI,		//Triangle icon in menu
		ICON_LINE,		//Line icon in menu
		ICON_CIRC,		//Circle icon in menu
		ICON_SQUARE,	//Square icon in menu
		ICON_OVAL,		//Oval icon in menu
		ICON_REG_POLYGON,	//Regular Polygon icon in menu





		ICON_Select,		//Select icon in menu
		
		ICON_SendBack,
		ICON_Delete,		//Delete icon in menu
		ICON_ROTATE,		//Rotate icon in menu
		ICON_COPY,		//Copy icon in menu
		ICON_PASTE,

		
		ICON_DRAW_CLR,
		ICON_FILL_CLR,

		ICON_SAVE,		//Save icon in menu
		ICON_LOAD,		//Load icon in menu


		ICON_EXIT,		//Exit icon

		DRAW_ICON_COUNT		//no. of menu icons ==> This should be the last line in this enum

	};




	int	width, height,	//Window width and height
		wx, wy,			//Window starting coordinates
		StatusBarHeight,	//Status Bar Height
		StatusBarWidth,
		ToolBarHeight,		//Tool Bar Height (distance from top of window to bottom line of toolbar)
		MenuIconWidth;		//Width of each icon in toolbar menu


	color DrawColor;		//Drawing color
	color FillColor;		//Filling color
	color HighlightColor;	//Highlighting color
	color MsgColor;			//Messages color
	color BkGrndColor;		//Background color
	color StatusBarColor;	//Status bar color
	int PenWidth;			//width of the pen that draws shapes
	

	/// Add more members if needed



	window* pWind;

public:

	GUI();

	// Input Functions  ---------------------------
	void GetPointClicked(int& x, int& y) const;//Get coordinate where user clicks
	string GetSrting() const;	 //Returns a string entered by the user
	operationType GetUseroperation() const; //Read the user click and map to an operation

	// Output Functions  ---------------------------
	window* CreateWind(int, int, int, int) const; //creates the application window
	void CreateDrawToolBar();	//creates Draw mode toolbar & menu
	void CreateStatusBar() const;	//create the status bar

	color CreateColorPalette();
	void DrawColorPalette();
	
	void SetDrawColor(color newColor); 
	void SetFillColor(color newColor);  

	
	

	void ClearStatusBar() const;	//Clears the status bar
	void ClearDrawArea() const;	//Clears the drawing area

	// -- shapes Drawing functions
	void DrawRect(Point P1, Point P2, GfxInfo RectGfxInfo) const;
	void DrawSquare(Point P1, Point P2, GfxInfo SquareGfxInfo) const;
	void DrawLine(Point P1, Point P2, GfxInfo LineGfxInfo) const;  //Draw a line
	void DrawCircle(Point Center, double Radius, GfxInfo CircGfxInfo) const;  //Draw a circle
	void DrawTriangle(Point P1, Point P2, Point P3, GfxInfo TriGfxInfo) const;  //Draw a triangle
	void DrawPolygon(Point vertices,int numSides, GfxInfo ShpGfxInfo) const;
	void DrawOval(Point P1, Point P2, GfxInfo OvalGfxInfo) const;

	
	

	///Make similar functions for drawing all other shapes.

	void PrintMessage(string msg) const;	//Print a message on Status bar
	color getCrntDrawColor() const;	//get current drwawing color
	color getCrntFillColor() const;	//get current filling color
	int getCrntPenWidth() const;		//get current pen width
	color GetHighlightColor() const;	//get current highlight color


	~GUI();
};

