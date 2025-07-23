#pragma once
#include "Operations/operation.h"

class opDrawColor : public operation
{
public:
    opDrawColor(controller* pCont);
    virtual void Execute();
};
