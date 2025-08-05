#pragma once
#include "Operations/operation.h"
#include "controller.h"

class opAddIrregularPoly : public operation
{
public:
    opAddIrregularPoly(controller* pCont);
    virtual ~opAddIrregularPoly();

    virtual void Execute();
}; 