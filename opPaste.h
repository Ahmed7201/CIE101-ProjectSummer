#pragma once
#pragma once
#include "Operations/operation.h"


class opPaste : public operation {
public:
    opPaste(controller* pCont);
    virtual void Execute();
};
