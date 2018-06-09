#include "NumericBox.h"

NumericBox::NumericBox(short top, short left, int max, int min, int value)
{
	_top = top;
	_left = left;
	_max = max;
	_min = min;
	_value = value;
	_width = 2*ONE_CHAR_BUTTON_WIDTH + to_string(value).size() + NUMERIC_BOX_LABEL_SPACE_MARGIN;	// accomodates box's 2 buttons, label and spaces
	_height = ONE_CHAR_BUTTON_HEIGHT;	
	initChildren(value);
	
	_focusable = false;
	setFrameType(SINGLE_SOLID);
}

NumericBox::~NumericBox()
{
}


void
NumericBox::initChildren(int val)
{
	//create buttons and add as children
	add(_min_button = new Button("-"));
	add(numeric_label = new Label(to_string(val)));
	add(_plus_button = new Button("+"));

	//init buttons color and position relative to box
	_min_button->setLeft(_left);
	_min_button->setTop(_top);
	_min_button->setColor(Color::Black, Color::Orange);

	numeric_label->setLeft(_left + ONE_CHAR_BUTTON_WIDTH);
	numeric_label->setTop(_top);
	numeric_label->setHeight(ONE_CHAR_BUTTON_HEIGHT);
	numeric_label->setColor(Color::Black, Color::Orange);

	_plus_button->setLeft(numeric_label->getLeft() + numeric_label->getWidth() + NUMERIC_BOX_LABEL_SPACE_MARGIN);
	_plus_button->setTop(_top);
	_plus_button->setColor(Color::Black, Color::Orange);

	char* fn = __FUNCTION__;
	debug(PG_DBG_INFO, "%s: ended. %d: top	%d: left ", fn, _top, _left);

}

bool
NumericBox::mousePressed(int x, int y, bool isLeft, Graphics& g)
{
	//check if clicked minus or plus Button
	if (isInside(x, y, _min_button->getLeft(), _min_button->getTop(), _min_button->getWidth(), _min_button->getHeight())) {
		dec();
		return true;
	}
	else if (isInside(x, y, _plus_button->getLeft(), _plus_button->getTop(), _plus_button->getWidth(), _plus_button->getHeight())) {
		inc();
		return true;
	}
	return false;
}

void
NumericBox::inc()
{
	if ( _value + 1 <= _max) {
		numeric_label->setValue(to_string(++_value));
	}
}

void
NumericBox::dec()
{
	if (_value - 1 >= _min) {
		numeric_label->setValue(to_string(--_value));
	}
	
}

void
NumericBox::draw(Graphics& g)
{
	Control::draw(g);
}
