#pragma once
#include "Operations/operation.h"

class opUndo : public operation {
public:
    opUndo(controller* pCont);
    virtual void Execute();
};