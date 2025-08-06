#pragma once
#include "Operations/operation.h"
class opResize_by_Drag :
    public operation
{
public:
	opResize_by_Drag(controller* pCont);
	void Execute() override;
	virtual ~opResize_by_Drag();
};

