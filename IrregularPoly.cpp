#include "IrregularPoly.h"
#include <fstream>
#include <cmath>

IrregularPoly::IrregularPoly(Point* vertices, int numVertices, GfxInfo shapeGfxInfo) : shape(shapeGfxInfo)
{
    NumVertices = numVertices;
    Vertices = new Point[NumVertices];

    // Copy vertices
    for (int i = 0; i < NumVertices; i++) {
        Vertices[i] = vertices[i];
    }

    // Calculate center point (average of all vertices)
    int sumX = 0, sumY = 0;
    for (int i = 0; i < NumVertices; i++) {
        sumX += Vertices[i].x;
        sumY += Vertices[i].y;
    }
    Center.x = sumX / NumVertices;
    Center.y = sumY / NumVertices;
}

IrregularPoly::~IrregularPoly()
{
    delete[] Vertices;
}

void IrregularPoly::Draw(GUI* pUI) const
{
	// Check if the shape has an image attached
	if (HasImage()) {
		// Create a temporary graphics info without fill for the border
		GfxInfo borderInfo = ShpGfxInfo;
		borderInfo.isFilled = false; // Don't fill when we have an image
		
		// Draw the shape border first
		pUI->DrawIrregularPoly(Vertices, NumVertices, borderInfo);
		
		// Calculate the polygon bounding box
		int minX = Vertices[0].x, minY = Vertices[0].y;
		int maxX = Vertices[0].x, maxY = Vertices[0].y;
		
		for (int i = 1; i < NumVertices; i++) {
			minX = min(minX, Vertices[i].x);
			minY = min(minY, Vertices[i].y);
			maxX = max(maxX, Vertices[i].x);
			maxY = max(maxY, Vertices[i].y);
		}
		
		int width = maxX - minX;
		int height = maxY - minY;
		
		// Draw the image inside the shape (this will be drawn on top of the border)
		pUI->DrawImage_InsideShape(GetImagePath(), minX, minY, width, height);
	} else {
		// Draw the shape normally with fill
		pUI->DrawIrregularPoly(Vertices, NumVertices, ShpGfxInfo);
	}
}

bool IrregularPoly::isInside(int x, int y) const
{
    // Use ray-casting algorithm to determine if point is inside polygon
    bool inside = false;

    for (int i = 0, j = NumVertices - 1; i < NumVertices; j = i++) {
        if (((Vertices[i].y > y) != (Vertices[j].y > y)) &&
            (x < (Vertices[j].x - Vertices[i].x) * (y - Vertices[i].y) /
                (Vertices[j].y - Vertices[i].y + 1e-10) + Vertices[i].x)) {
            inside = !inside;
        }
    }

    return inside;
}

string IrregularPoly::GetShapeType() const
{
    return "IrregularPoly";
}

void IrregularPoly::Rotate(double degrees)
{
    // Use a constant for pi since M_PI might not be defined
    const double PI = 3.14159265358979323846;
    // Convert degrees to radians
    double radians = degrees * PI / 180.0;

    // Rotate each vertex around the center
    for (int i = 0; i < NumVertices; i++) {
        // Calculate relative position from center
        double dx = Vertices[i].x - Center.x;
        double dy = Vertices[i].y - Center.y;

        // Apply rotation matrix
        double newDx = dx * cos(radians) - dy * sin(radians);
        double newDy = dx * sin(radians) + dy * cos(radians);

        // Update vertex position
        Vertices[i].x = Center.x + newDx;
        Vertices[i].y = Center.y + newDy;
    }
}

shape* IrregularPoly::Clone()
{
    return new IrregularPoly(*this);
}

void IrregularPoly::Move(int dx, int dy)
{
    // Move all vertices and center
    for (int i = 0; i < NumVertices; i++) {
        Vertices[i].x += dx;
        Vertices[i].y += dy;
    }
    Center.x += dx;
    Center.y += dy;
}

void IrregularPoly::Scale(double factor)
{
    // Scale all vertices relative to the center
    for (int i = 0; i < NumVertices; i++) {
        double dx = Vertices[i].x - Center.x;
        double dy = Vertices[i].y - Center.y;
        Vertices[i].x = Center.x + dx * factor;
        Vertices[i].y = Center.y + dy * factor;
    }
}

void IrregularPoly::Save(ofstream& OutFile)
{
    OutFile << "IrregularPoly " << NumVertices;
    for (int i = 0; i < NumVertices; i++) {
        OutFile << " " << Vertices[i].x << " " << Vertices[i].y;
    }
    OutFile << endl;

    OutFile << (int)ShpGfxInfo.DrawClr.ucRed << " "
        << (int)ShpGfxInfo.DrawClr.ucGreen << " "
        << (int)ShpGfxInfo.DrawClr.ucBlue << endl;
    OutFile << (int)ShpGfxInfo.FillClr.ucRed << " "
        << (int)ShpGfxInfo.FillClr.ucGreen << " "
        << (int)ShpGfxInfo.FillClr.ucBlue << endl;
    OutFile << ShpGfxInfo.isFilled << endl;
}

void IrregularPoly::Load(ifstream& Infile)
{
    Infile >> NumVertices;

    // Delete existing vertices if any
    if (Vertices) {
        delete[] Vertices;
    }

    Vertices = new Point[NumVertices];

    // Load vertices
    for (int i = 0; i < NumVertices; i++) {
        Infile >> Vertices[i].x >> Vertices[i].y;
    }

    // Calculate center
    int sumX = 0, sumY = 0;
    for (int i = 0; i < NumVertices; i++) {
        sumX += Vertices[i].x;
        sumY += Vertices[i].y;
    }
    Center.x = sumX / NumVertices;
    Center.y = sumY / NumVertices;

    // Load colors
    int r, g, b;

    // Draw Color
    Infile >> r >> g >> b;
    ShpGfxInfo.DrawClr.ucRed = static_cast<unsigned char>(r);
    ShpGfxInfo.DrawClr.ucGreen = static_cast<unsigned char>(g);
    ShpGfxInfo.DrawClr.ucBlue = static_cast<unsigned char>(b);

    // Fill Color
    Infile >> r >> g >> b;
    ShpGfxInfo.FillClr.ucRed = static_cast<unsigned char>(r);
    ShpGfxInfo.FillClr.ucGreen = static_cast<unsigned char>(g);
    ShpGfxInfo.FillClr.ucBlue = static_cast<unsigned char>(b);

    // Fill flag
    Infile >> ShpGfxInfo.isFilled;
}

Point IrregularPoly::Getcenter() const
{
    return Center;
}
void IrregularPoly::Resize(double newWidth, double newHeight)
{
    // Calculate the current bounding box
    int minX = Vertices[0].x, minY = Vertices[0].y;
    int maxX = Vertices[0].x, maxY = Vertices[0].y;
    for (int i = 1; i < NumVertices; i++) {
        minX = min(minX, Vertices[i].x);
        minY = min(minY, Vertices[i].y);
        maxX = max(maxX, Vertices[i].x);
        maxY = max(maxY, Vertices[i].y);
    }
    // Calculate current width and height
    double currentWidth = maxX - minX;
    double currentHeight = maxY - minY;
    // Calculate scale factors
    double widthFactor = newWidth / currentWidth;
    double heightFactor = newHeight / currentHeight;
    // Scale each vertex
    for (int i = 0; i < NumVertices; i++) {
        Vertices[i].x = Center.x + (Vertices[i].x - Center.x) * widthFactor;
        Vertices[i].y = Center.y + (Vertices[i].y - Center.y) * heightFactor;
    }
}
