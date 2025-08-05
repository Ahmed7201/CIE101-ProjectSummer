#pragma once
#include "Operations/operation.h"

class opDrawColor : public operation
{
public:
    opDrawColor(controller* pCont);
	virtual ~opDrawColor();
    virtual void Execute() override;
};
