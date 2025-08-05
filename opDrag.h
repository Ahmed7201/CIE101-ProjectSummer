#pragma once
#include "Operations/operation.h"

class opDrag : public operation {
public:
    opDrag(controller* pCont);
    virtual void Execute();
};