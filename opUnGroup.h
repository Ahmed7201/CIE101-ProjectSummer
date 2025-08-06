#pragma once
#include "Operations/operation.h"
//Ahmed Ghoneim
class opUnGroup : public operation
{
public:
	opUnGroup(controller* pCont);
	virtual ~opUnGroup();
	virtual void Execute();
}; 