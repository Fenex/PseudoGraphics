#include "NumericBox.h"

NumericBox::NumericBox(int max = MAX_NUMERIC_VAL, int min = MIN_NUMERIC_VAL, string value = DEF_NUMERIC_VAL)
{
	add(new Button("-"));
	add(new Button("+"));
	add(new Label(value));
	_focusable = false;
	setFrameType(SINGLE_SOLID);
}

NumericBox::~NumericBox()
{
}
