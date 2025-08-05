#pragma once
#include "Operations/operation.h"

class opExit : public operation
{
public:
    opExit(controller* pCont);
    virtual void Execute() override;
  virtual ~opExit();
};