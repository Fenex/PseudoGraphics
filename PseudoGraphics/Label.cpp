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
	_dim_x = value.size() + BORDER_OFFSET;
	_dim_y = BORDER_OFFSET + 1;

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
	g.moveTo(left+1, top+1);
	g.write(value);
	g.moveTo(left, top);
}

bool
Label::myPureFunction() {
	return false;
}
