#pragma once
#include "Operations/operation.h"
class opStickImage :
    public operation
{
public:
    opStickImage(controller* pCont);  // Constructor
    virtual void Execute() override;   // Execute the operation to stick an image
	virtual ~opStickImage();           // Destructor
};

