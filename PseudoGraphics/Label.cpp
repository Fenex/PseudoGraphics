#include "Label.h"


Label::Label() : Control()
{
	char* fn = __FUNCTION__;
	debug(PG_DBG_INFO, "%s: called.", fn);
	setValue(DEFAULT_LABEL_STR);
	_frame_type = NONE;
}

Label::Label(string value) : 
	Control()
{
	Label::Label();
	setValue(value);
}

string
Label::getValue()
{
    return this->value;
}

void
Label::setValue(string value)
{
	_width = value.size() + BORDER_OFFSET;
	_height = BORDER_OFFSET + 1;

  this->value = value;
}


void
Label::draw(Graphics& g, int x, int y, size_t z)
{
    if (!z)
        g.write(value);

}

void
Label::draw(Graphics& g) {
	Control::draw(g);
	g.moveTo(_left+1, _top+1);
	g.write(value);
	g.moveTo(_left, _top);
}

bool
Label::myPureFunction() {
	return false;
}
