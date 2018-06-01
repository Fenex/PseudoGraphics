#pragma once

#include "Label.h"
class Button : public Label
{

public:
	Button();
	Button(string& s);
	Button(const char* s);
	virtual ~Button();
	virtual bool myPureFunction();
};

