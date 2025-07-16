#pragma once  
#include "Operations/operation.h"  
#include "controller.h" // Ensure the correct relative path is used  

class opAddCircle : public operation  
{  
public:  
	opAddCircle(controller* pCont);  

	virtual ~opAddCircle();  

	virtual void Execute(); //Add circle to the controller  
};
