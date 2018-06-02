#include "NumericBox.h"

NumericBox::NumericBox(int max, int min, int value)
{
	
	_max = max;
	_min = min;
	_width = 6 + to_string(value).size();	// labelSize + 2*buttonSize
	_height = 3;
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
void
NumericBox::draw(Graphics& g)
{
	Control::draw(g);
}
