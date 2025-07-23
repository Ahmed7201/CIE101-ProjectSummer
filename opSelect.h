#pragma once
#include "Operations/operation.h"
#include "Shapes/shape.h"
class opSelect :
    public operation
{
public:
    opSelect(controller* pCont);
        virtual void Execute() override; // Execute the operation
        virtual ~opSelect(); // Destructor
       
};

