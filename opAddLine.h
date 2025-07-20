#pragma once
#include "Operations/operation.h"
#include "controller.h"
class opAddLine :
    public operation
{
public:
    opAddLine(controller* pcont);

    virtual ~opAddLine();

    virtual void Execute();

};

