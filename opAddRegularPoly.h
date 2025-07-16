#pragma once
#include "Operations/operation.h"
#include "controller.h"

class opAddRegularPoly :public operation 
{
public:
	opAddRegularPoly(controller* pCont);
	virtual ~opAddRegularPoly();

	//Add Regular Polygon to the controller
	virtual void Execute();


};

