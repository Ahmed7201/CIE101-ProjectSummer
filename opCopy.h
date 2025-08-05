#pragma once
#include "Operations/operation.h"
class opCopy :
    public operation
{
public:
    opCopy(controller* pCont);
    virtual void Execute() override; 
	virtual ~opCopy(); 
};

