#pragma once
#include "Operations/operation.h"
#include <string>
using namespace std;

class opSave : public operation
{
public:
	opSave(controller* pCont);           // Constructor without filename
	virtual void Execute() override;     // Ask user for filename and save
	virtual ~opSave();                   // Destructor
};
