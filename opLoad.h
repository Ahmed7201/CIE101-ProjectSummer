#pragma once
#include "Operations/operation.h"
class opLoad :
    public operation
{
    private:
		string filename; // Name of the file to load shapes from
public:
    opLoad(controller* pCont);
    virtual void Execute() override; // Execute the load operation
	virtual ~opLoad(); // Destructor

};

