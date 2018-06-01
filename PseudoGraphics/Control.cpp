#include "Control.h"


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
	ofstream file;
	time_t now = time(0);
	tm *ltm = localtime(&now);

	file.open(DBG_FILE_NAME, std::ios_base::app);
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

Control::Control()
{
}


Control::~Control()
{
}


void
Control::draw(Graphics& g) {
	const char* fn = __FUNCTION__;
	debug(PG_DBG_INFO, "%s: called.", fn);
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
	
	//old: SetConsoleCursorPosition(_out, _base_pos);
	g.moveTo(left, top);


	if (_frame_type == NONE) {
		for (int i = 0; i < this->_dim_y; ++i) {
			//draw empty lines as border
			drawLine(SPACE, SPACE, SPACE);
			
			//old: SetConsoleCursorPosition(_out, { _base_pos.X,_base_pos.Y + (short)i + 1 });
			g.moveTo(left, top+ (short)i + 1);

		}
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

	//old: SetConsoleCursorPosition(_out, { _base_pos.X,_base_pos.Y + 1 });
	g.moveTo(left, top + 1);

	for (size_t i = 0; i < _dim_y - 2; i++) {
		drawLine(line_vert, SPACE, line_vert);

		//old :SetConsoleCursorPosition(_out, { _base_pos.X,_base_pos.Y + 2 + ((short)i) });
		g.moveTo(left, top + (short)i + 2);
	}

	drawLine(btm_left, line_horiz, btm_right);

	//old: SetConsoleCursorPosition(_out, { _base_pos.X + 1,_base_pos.Y + 1 });
	g.moveTo(left + 1, top + 1);


	//reset our cursor pos to base pos again
	
	//old: SetConsoleCursorPosition(_out, _base_pos);
	g.moveTo(left, top);
}

void
Control::drawChildren(Graphics& g) {
	for each (Control* child in _children) {
		child->draw(g);
	}
}

void
Control::drawLine(char open_sym, char mid_sym, char end_sym) {
	char* fn = __FUNCTION__;
	debug(PG_DBG_INFO, "%s: called.", fn);

	for (size_t i = 0; i < _dim_x - 1; i++) {
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
Control::getChildren() {
	return _children;
}