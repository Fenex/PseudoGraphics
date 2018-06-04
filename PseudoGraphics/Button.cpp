#include "Button.h"



Button::Button() : Label()
{
	_focusable = false;
	_clickable = true;
	setFrameType(SINGLE_SOLID);
	fixDimensions();
}

Button::Button(string& s) : Button()
{
	setValue(s);
	fixDimensions();
	setHeight(DIM_DEF_H);
}

Button::Button(const char* s) : Button(string(s))
{
}

Button::~Button()
{
}

void
Button::fixDimensions()
{
	_width = getValue().size() + BORDER_OFFSET + 1;
}


bool
Button::mousePressed(int x, int y, bool isLeft)
{
	char* fn = __FUNCTION__;
	bool result = false;

	debug(PG_DBG_INFO, "%s: called.", fn);
	debug(PG_DBG_INFO, "%s: x=%d, y=%d, isLeft=%d.", fn, x, y, isLeft);

	if (isLeft) {
		
		setColor(_foreground, _background);
		result = true;
	}

	return result;
}


bool
Button::myPureFunction()
{
	return false;
}

