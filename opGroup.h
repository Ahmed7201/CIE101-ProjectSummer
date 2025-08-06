#pragma once
#include "Operations/operation.h"

class opGroup : public operation
{
public:
	opGroup(controller* pCont);
	virtual ~opGroup();
	virtual void Execute();
}; 