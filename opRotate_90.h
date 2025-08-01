#pragma once
#include "Operations/operation.h"
class opRotate_90 :
    public operation
{
public:
	opRotate_90(controller* pCont);

	virtual ~opRotate_90();

	virtual void Execute() override;
};

