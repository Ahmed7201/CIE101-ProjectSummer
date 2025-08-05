#pragma once
#include "Shapes/Shape.h"

class IrregularPoly : public shape
{
private:
    Point* Vertices;     // Array of vertices
    int NumVertices;     // Number of vertices
    Point Center;        // Center point (calculated from vertices)

public:
    IrregularPoly(Point* vertices, int numVertices, GfxInfo shapeGfxInfo);
    virtual ~IrregularPoly();
    virtual void Draw(GUI* pUI) const;
    virtual bool isInside(int x, int y) const override;
    virtual string GetShapeType() const override;
    virtual void Rotate(double degrees) override;
    virtual shape* Clone() override;
    virtual void Move(int dx, int dy) override;
    virtual void Save(ofstream& OutFile) override;
    virtual void Load(ifstream& Infile) override;
    virtual Point Getcenter() const override;
}; 