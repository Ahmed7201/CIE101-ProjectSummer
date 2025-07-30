#pragma once
#include "Operations/operation.h"
class opDelete :
    public operation
{
public:
        opDelete(controller* pCont);
    virtual void Execute() override;
	virtual ~opDelete();
};

