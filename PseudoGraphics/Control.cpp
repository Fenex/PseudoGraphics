#include "Control.h"

Control* Control::_focused_control = NULL;


Control*
Control::getFocus()
{
	return _focused_control;
}

void
Control::setFocus(Control& control)
{
	_focused_control = &control;
}

static bool
isValidPos(const int &size, const int &pos) {
	if (pos < 0 || pos > size) {
		return false;
	}
	return true;

}

static const char*
dbgToString(DebugLevel lvl) {
	switch (lvl)
	{
	case PG_DBG_INFO:
		return PG_INFO;
	case PG_DBG_ERROR:
		return PG_ERR;
	default:
		return PG_STANDARD;
	}
}

void
debug(DebugLevel lvl, const char *format, ...) {
	
	static bool isEmpty = true;
	//change DEBUG_ON to 1 on Constants.h to turn debug on
	if (!DEBUG_ON)
		return;

	ofstream file;
	time_t now = time(0);
	tm *ltm = localtime(&now);

	if (isEmpty)
	{
		file.open(DBG_FILE_NAME);
		isEmpty = false;
	}
	else
	{
		file.open(DBG_FILE_NAME, std::ios_base::app);
	}
	char buffer[512] = { 0 };


	va_list args;
	va_start(args, format);
	vsprintf(buffer, format, args);

	file << "{" << ltm->tm_hour << ":";
	file << ltm->tm_min << ":";
	file << ltm->tm_sec << "}";
	file << " [" << dbgToString(lvl) << "] " << buffer << "\n";
	va_end(args);
	file.close();
}

Control::Control() : _focusable(true), _left(0), _top(0), _width(0), _height(0) {}


Control::~Control() {}


void
Control::draw(Graphics& g) {
	const char* fn = __FUNCTION__;
	debug(PG_DBG_INFO, "%s: called.", fn);
	g.setBackground(_background);
	g.setForeground(_foreground);
	drawBorder(g);
	drawChildren(g);
}

void
Control::drawBorder(Graphics& g) {
	const char* fn = __FUNCTION__;
	debug(PG_DBG_INFO, "%s: called.", fn);

	char top_left, top_right, btm_left, btm_right;
	char line_horiz, line_vert;

	//reset our cursor pos to base pos
	g.moveTo(_left, _top);

	if (_frame_type == NONE) {
		//for (int i = 0; i < this->_height; ++i) {
		//	//draw empty lines as border
		//	drawLine(SPACE, SPACE, SPACE);
		//	g.moveTo(_left, _top+ (short)i + 1);

		//}
		return;
	}

	//handle the single | double scenario:
	top_left = (_frame_type == SINGLE_SOLID ? SINGLE_TOP_LEFT_CORNER : DOUBLE_TOP_LEFT_CORNER);
	top_right = (_frame_type == SINGLE_SOLID ? SINGLE_TOP_RIGHT_CORNER : DOUBLE_TOP_RIGHT_CORNER);
	btm_left = (_frame_type == SINGLE_SOLID ? SINGLE_BTM_LEFT_CORNER : DOUBLE_BTM_LEFT_CORNER);
	btm_right = (_frame_type == SINGLE_SOLID ? SINGLE_BTM_RIGHT_CORNER : DOUBLE_BTM_RIGHT_CORNER);
	line_horiz = (_frame_type == SINGLE_SOLID ? SINGLE_LINE_HORIZONTAL : DOUBLE_LINE_HORIZONTAL);
	line_vert = (_frame_type == SINGLE_SOLID ? SINGLE_LINE_VERTICAL : DOUBLE_LINE_VERTICAL);

	drawLine(top_left, line_horiz, top_right);
	g.moveTo(_left, _top + 1);

	for (short i = 0; i < _height - 2; i++) {
		drawLine(line_vert, SPACE, line_vert);
		g.moveTo(_left, _top + (short)i + 2);
	}

	drawLine(btm_left, line_horiz, btm_right);

	g.moveTo(_left + 1, _top + 1);

	//reset our cursor pos to base pos again
	g.moveTo(_left, _top);
}

void
Control::drawChildren(Graphics& g) {
	char* fn = __FUNCTION__;
	debug(PG_DBG_INFO, "%s: called.", fn);

	for each (Control* child in _children) {
		child->draw(g);
	}
}

void
Control::drawLine(char open_sym, char mid_sym, char end_sym) {

	for (short i = 0; i < _width - 1; i++) {
		if (i == 0) {
			cout << open_sym;
		}
		else {
			cout << mid_sym;
		}
	}
	cout << end_sym;
}


vector<Control*> 
Control::getChildren() 
{
	return _children;
}

void 
Control::setFrameType(FrameType frame_type)  
{
	_frame_type = frame_type;
}

void 
Control::setColor(Color bg, Color fg) 
{
	_background = bg;
	_foreground = fg;
}

short 
Control::getWidth()
{
	return _width;
}

short 
Control::getHeight()
{
	return _height;
}

bool 
Control::canGetFocus() 
{ 
	return _focusable; 
}

bool 
Control::canBeClicked()
{
	return _clickable;
}


void 
Control::getAllControls(vector<Control*>* controls) 
{
	controls = &_children;
}

static bool
isInValidRange(short val) {
	if (val >= 0) {
		return true;
	}
	return false;
}

//todo: turn these next 2 functions into one
void 
Control::setTop(short y)
{
	//todo: validate range of value
	short child_base_y;
	short diff_y = abs(y - _top);

	_top = y;

	for each (Control* child in _children) {
		child_base_y = child->getTop();
		child->setTop(diff_y + child_base_y);
	}

}

void 
Control::setLeft(short x)
{
	//todo: validate range of value
	short child_base_x;
	short diff_x = abs(x - _left);

	_left = x;
	
	for each (Control* child in _children) {
		child_base_x = child->getLeft();
		child->setLeft(diff_x + child_base_x);
	}

}

void 
Control::setWidth(short x)
{
	if (isInValidRange(x))
		_width = x;
}

void 
Control::setHeight(short y)
{
	if (isInValidRange(y))
		_height = y;
}

void 
Control::add(Control* child)
{
	const char* fn = __FUNCTION__;
	debug(PG_DBG_INFO, "%s: called.", fn);
	debug(PG_DBG_INFO, "%s: new_child=%d.", fn, child);

	if (child) {
		//fix (update) child's position in relation to this parent:
		child->setLeft(_left + child->getLeft());
		child->setTop(_top + child->getTop());

		_children.push_back(child);
	}
	else {
		debug(PG_DBG_ERROR, "%s: trying to add a child which is null.", fn);
	}
}

bool 
Control::mousePressed(int x, int y, bool isLeft) {
	const char* fn = __FUNCTION__;
	debug(PG_DBG_INFO, "%s: called.", fn);
	
	if (isLeft)
	{
		for each (Control* child in _children)
		{
			debug(PG_DBG_INFO, "%s: child={%d,%d}.", fn, child->_left, child->_top);

			if (isInside(x, y, child->_left, child->_top, child->_width, child->_height))
			{
				debug(PG_DBG_INFO, "%s: found the clicked child.", fn);
				setFocus(*child);
				return child->mousePressed(x, y, isLeft);
			}
		}
	}
	else 
	{
		debug(PG_DBG_ERROR, "%s: right click is not supported right now.", fn);
	}
	return false;
}

void 
Control::setClickable(bool clickable)
{
	_clickable = clickable;
}

void 
Control::setFocusable(bool focusable)
{
	_focusable = focusable;
}

