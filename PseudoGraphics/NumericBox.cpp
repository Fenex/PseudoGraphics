#include "NumericBox.h"

NumericBox::NumericBox(int max, int min, int value)
{
	
	_max = max;
	_min = min;
	_value = value;
	_width = 6 + to_string(value).size() + 2;	// 2*buttonSize + labelSize + 2*space
	_height = 3;	//button height
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
	add(minButton = new Button("-"));
	add(numericLabel = new Label(to_string(val)));
	add(plusButton = new Button("+"));

	//init buttons color and position relative to box
	minButton->setLeft(_left);
	minButton->setTop(_top);
	minButton->setColor(Color::Black, Color::Orange);

	numericLabel->setLeft(_left + 3);
	numericLabel->setTop(_top);
	numericLabel->setHeight(3);
	numericLabel->setColor(Color::Black, Color::Orange);

	plusButton->setLeft(numericLabel->getLeft() + numericLabel->getWidth() + 2);
	plusButton->setTop(_top);
	plusButton->setColor(Color::Black, Color::Orange);

}

bool
NumericBox::mousePressed(int x, int y, bool isLeft)
{
	//check if clicked minus or plus Button
	if (isInside(x, y, minButton->getLeft(), minButton->getTop(), minButton->getWidth(), minButton->getHeight())) {
		dec();
		return true;
	}
	else if (isInside(x, y, plusButton->getLeft(), plusButton->getTop(), plusButton->getWidth(), plusButton->getHeight())) {
		inc();
		return true;
	}
	return false;
}

void
NumericBox::inc()
{
	if ( _value + 1 <= _max) {
		numericLabel->setValue(to_string(++_value));
	}
}

void
NumericBox::dec()
{
	if (_value - 1 >= _min) {
		numericLabel->setValue(to_string(--_value));
	}
	
}

void
NumericBox::draw(Graphics& g)
{
	Control::draw(g);
}
