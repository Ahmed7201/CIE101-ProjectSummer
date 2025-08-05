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
    // Draw lines between consecutive vertices to form the polygon
    for (int i = 0; i < NumVertices; i++) {
        Point P1 = Vertices[i];
        Point P2 = Vertices[(i + 1) % NumVertices]; // Connect last vertex to first
        
        pUI->DrawLine(P1, P2, ShpGfxInfo);
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