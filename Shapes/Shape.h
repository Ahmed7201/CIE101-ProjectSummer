#pragma once
#include "..\defs.h"
#include "..\GUI\GUI.h"


//Base class for all shapes
class shape
{
protected:
	int ID;		//Each shape has an ID
	GfxInfo ShpGfxInfo;	//shape graphis info
	string imagePath; // Path to the image associated with the shape, if any
	
	/// Add more parameters if needed.

public:
	shape(GfxInfo shapeGfxInfo);
	virtual ~shape() {}
	void SetSelected(bool s);	//select/unselect the shape
	bool IsSelected() const;	//check whether fig is selected
	virtual bool isInside(int x, int y) const=0; //check whether a point is inside the shape
	void SetGfxInfo(GfxInfo gfxInfo);  //set the shape's graphical info

	

	GfxInfo GetGfxInfo() const; //get the shape's graphical info

	virtual string GetShapeType() const = 0; // Added to get the shape type

	virtual Point Getcenter() const=0; // Get the center point of the shape
	

	
	static double CalcRadius(Point center, Point edge);
	
	virtual void Draw(GUI* pUI) const  = 0 ;		//Draw the shape
	
	void ChngDrawClr(color Dclr);	//changes the shape's drawing color
	void ChngFillClr(color Fclr);	//changes the shape's filling color

	///The following functions should be supported by the shape class
	///It should be overridden by each inherited shape

	///Decide the parameters that you should pass to each function	
	virtual shape* Clone() = 0;
	virtual void Move(int dx, int dy) = 0;	//Move the shape by dx, dy
	virtual void Rotate(double degrees) = 0;	//Rotate the shape
	//virtual void Resize() = 0;	//Resize the shape
	//virtual void Move() = 0;		//Move the shape



	virtual void Save(ofstream &OutFile) = 0;	//Save the shape parameters to the file
	virtual void Load(ifstream &Infile) = 0;	//Load the shape parameters to the file

	void SetImagePath(const string& path); 
	string GetImagePath() const; 
	bool HasImage() const; 

	//virtual void PrintInfo(Output* pOut) = 0;	//print all shape info on the status bar
};

