#pragma once
#include "Operations/operation.h"

class opRedo : public operation {
public:
    opRedo(controller* pCont);
    virtual void Execute();
};
