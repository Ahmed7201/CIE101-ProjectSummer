#pragma once  
#include "Operations/operation.h" 

class opStickImage : public operation
{
public:
	opStickImage(controller* pCont);
	virtual ~opStickImage();
	virtual void Execute();
}; 