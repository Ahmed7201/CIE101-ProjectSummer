#pragma once  
#include "Operations/operation.h"  
#include "controller.h"

class opAddTriangle : public operation
{
public:
	opAddTriangle(controller* pCont);
	virtual ~opAddTriangle();

	//Add rectangle to the controller
	virtual void Execute();

};