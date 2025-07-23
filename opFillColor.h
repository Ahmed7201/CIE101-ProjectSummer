#pragma once
#include "Operations/operation.h"


class opFillColor : public operation
{
public:
    opFillColor(controller* pCont);
    virtual void Execute();
};