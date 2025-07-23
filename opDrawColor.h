#pragma once
#include <string>
#include "Operations/operation.h"

class opDrawColor : public operation
{
public:
	opDrawColor(controller* pCont);
	virtual ~opDrawColor();
	
	virtual void Execute();

};
