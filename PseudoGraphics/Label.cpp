#include "Label.h"


Label::Label() : 
	Control(), 
	value(DEFAULT_LABEL_STR) {

}

Label::Label(string value) : 
	Control(), 
	value(value) {

}

string
Label::getValue()
{
    return this->value;
}

void
Label::setValue(string value)
{
    this->value = value;
}


void
Label::draw(Graphics& g, int x, int y, size_t z)
{
    if (!z)
        g.write(value);

}

bool
Label::myPureFunction() {
	return false;
}
