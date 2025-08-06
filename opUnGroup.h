#pragma once
#include "Operations/operation.h"

class opUnGroup : public operation
{
public:
	opUnGroup(controller* pCont);
	virtual ~opUnGroup();
	virtual void Execute();
}; 