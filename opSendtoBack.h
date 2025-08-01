#pragma once
#include "Operations/operation.h"
class opSendtoBack :
    public operation
{
public:
    opSendtoBack(controller* pCont);
    virtual void Execute() override;
    virtual ~opSendtoBack();
};

