#pragma once
#ifndef BUTTON_H
#define BUTTON_H

#include "Label.h"
class Button : public Label
{

public:
	Button();
	Button(string& s);
	Button(const char* s);
	virtual ~Button();
	virtual bool myPureFunction();
	bool mousePressed(int x, int y, bool isLeft);
};

#endif // !BUTTON_H
