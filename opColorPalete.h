#pragma once
#include "Operations/operation.h"
class opColorPalete :
    public operation
{
public:
    opColorPalete(controller* pCont);
    ~opColorPalete();
    void Execute() override; //Execute the operation
};

