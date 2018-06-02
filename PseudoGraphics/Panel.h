#pragma once
#ifndef PANEL_H
#define PANEL_H

#include "Control.h"

class Panel :	public Control
{
public:
	Panel();
	virtual ~Panel();
	bool myPureFunction();
};


#endif // !PANEL_H