#include "Button.h"



Button::Button() : Label()
{
	_focusable = false;
	_clickable = true;
	setFrameType(SINGLE_SOLID);
}

Button::Button(string& s) : Button()
{
	setValue(s);
}

Button::Button(const char* s) : Button()
{
	string str(s);
	setValue(str);
}

Button::~Button()
{
}


bool
Button::mousePressed(int x, int y, bool isLeft)
{
	bool result = false;
	setValue("I've been clicked!");
	return result;
}

bool
Button::myPureFunction()
{
	return false;
}

