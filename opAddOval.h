#pragma once  
#include "Operations/operation.h"  
#include "controller.h" // Ensure the correct relative path is used  

class opAddOval : public operation
{
public:
	opAddOval(controller* pCont);

	virtual ~opAddOval();

	virtual void Execute(); //Add circle to the controller  
};
