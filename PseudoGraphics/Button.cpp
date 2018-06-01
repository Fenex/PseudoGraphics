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

//todo:
//bool
//Button::mousePressed()[
//
//]

bool
Button::myPureFunction()
{
	return false;
}

