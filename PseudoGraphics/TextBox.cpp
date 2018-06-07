#include "TextBox.h"

TextBox::TextBox()
{
	setClickable(true);
	setFocusable(true);
	setFrameType(SINGLE_SOLID);
}

TextBox::TextBox(short left = 0 , short top = 0, short width = 5, short height = 5) : Control()
{
	setLeft(left);
	setTop(top);
	setWidth(width);
	setHeight(height);
	setClickable(true);
	setFocusable(true);
	setFrameType(SINGLE_SOLID);
}


//draw the entire text box
void
TextBox::draw(Graphics& g) {
	char* fn = __FUNCTION__;
	debug(PG_DBG_INFO, fn, "called.");
	Control::draw(g);
}

bool
TextBox::mousePressed(int x, int y, bool isLeft)
{
	char* fn = __FUNCTION__;
	debug(PG_DBG_INFO, fn, "called.");

	//TODO: SHOW CURSOR (set visible)
	Graphics g;
	g.setBackground(_background);
	g.setForeground(_foreground);
	g.setCursorVisibility(true);

	//there could be 3 cases now:
	//1. pressing inside
	g.moveTo(_left + 1, _top + 1);

	return true;
}

/*
// keep user input in borders:
void
TextBox::handleInput() {
	char* fn = __FUNCTION__;
	debug(PG_DBG_INFO, fn, "called.");

	INPUT_RECORD record;
	DWORD read_bytes, fdw_mode;
	CONSOLE_SCREEN_BUFFER_INFO info;

	fdw_mode = ENABLE_WINDOW_INPUT | ENABLE_EXTENDED_FLAGS;
	//	fdw_mode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS;

	ReadConsoleInput(_in, &record, 1, &read_bytes);
	SetConsoleMode(_in, fdw_mode);


	switch (record.EventType) {
	case MOUSE_EVENT:
		//TODO: implement mouse event
	case KEY_EVENT:
		GetConsoleScreenBufferInfo(_in, &info);
		if (record.Event.KeyEvent.bKeyDown) {

			if (record.Event.KeyEvent.uChar.AsciiChar == BACKSPACE) {
				if (GetConsoleCursorPosition(_out).X - 1 == _coord.X) {
					if (GetConsoleCursorPosition(_out).Y - 1 > _coord.Y) {
						SetConsoleCursorPosition(_out, { _coord.X + _dim.X - BORDER_OFFSET ,GetConsoleCursorPosition(_out).Y - ((short)1) });
					}
					else {
						break;
					}
				}
				else {
					cout << BACKSPACE << CHAR_RESET;
					SetConsoleCursorPosition(_out, { GetConsoleCursorPosition(_out).X - 1 ,GetConsoleCursorPosition(_out).Y });
				}
			}

			else if (GetConsoleCursorPosition(_out).X + 1 == _dim.X + _coord.X) {
				if (GetConsoleCursorPosition(_out).Y < _dim.Y + _coord.Y) {
					SetConsoleCursorPosition(_out, { _coord.X + 1,GetConsoleCursorPosition(_out).Y + ((short)1) });
				}
			}
			else {
				cout << record.Event.KeyEvent.uChar.AsciiChar;
			}
		}
		break;
	}
}



*/


bool 
TextBox::myPureFunction()
{
	return true;
}