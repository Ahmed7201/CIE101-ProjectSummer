#pragma once
#include "Operations/operation.h"
#include "controller.h"
class opAddSquare : public operation
{
	public:
	opAddSquare(controller* pCont);
	virtual ~opAddSquare();

	virtual void Execute();
};

