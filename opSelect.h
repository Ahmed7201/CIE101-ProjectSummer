#pragma once
#include "Operations/operation.h"
#include "Shapes/shape.h"
class opSelect :
    public operation
{
    private:
		Point P1; // The point to select
		shape* selectedShape; // Pointer to the selected shape
public:
    opSelect(controller* pCont);
        virtual void Execute() override; // Execute the operation
        virtual ~opSelect(); // Destructor
       
};

