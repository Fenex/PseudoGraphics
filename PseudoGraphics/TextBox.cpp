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

void
TextBox::drawValue()
{
	Graphics g;
	short exact_row_size = getWidth() - (BORDER_OFFSET * 2);
	short exact_col_size = getHeight() - (BORDER_OFFSET * 2);;


	g.moveTo(_left + 1, _top + 1);
	for (short i = 0, j = 0; i < _value.size() ; i++)
	{
		//if we reached maximum box 
		if (i == exact_col_size*exact_row_size)
		{
			return;
		}

		if (((i != 0) && (i % exact_row_size)) == 0)
		{
			g.moveTo(_left + 1, (_top + BORDER_OFFSET) + (j++));
			setBoxCursorY(getBoxCursorY() + 1);
			//setBoxCursorY(_top + j);			
		}

		string temp_str;
		temp_str.push_back(_value.at(i));
		g.write(temp_str);
		setBoxCursorX(getBoxCursorX() + 1);
		//setBoxCursorX(_left + (i % exact_row_size) + BORDER_OFFSET*2);
		
	}

}

//draw the entire text box
void
TextBox::draw(Graphics& g) {
	char* fn = __FUNCTION__;
	debug(PG_DBG_INFO, fn, "called.");	
	Control::draw(g);
	drawValue();
}

void
TextBox::setBoxCursorX(short x)
{
	if (x >= _left && x <= _left + _width)
	{
		_box_cursor_x = x;
	}		
}

void
TextBox::setBoxCursorY(short y)
{
	if (y >= _top && y <= _top + _height)
	{
		_box_cursor_y = y;
	}
	
}

short
TextBox::getBoxCursorX()
{
	return _box_cursor_x;
}
short
TextBox::getBoxCursorY()
{
	return _box_cursor_y;
}

//short
//TextBox::getBoxCursorX()
//{
//	int exact_row_size = getWidth() - (BORDER_OFFSET * 2);
//	return getLeft() + BORDER_OFFSET + (_value.size() % exact_row_size);
//}
//short
//TextBox::getBoxCursorY()
//{
//	int exact_col_size = getHeight() - (BORDER_OFFSET * 2);
//	return getTop() + BORDER_OFFSET + (_value.size() / exact_col_size);
//}


//this func returns the maximum x,y coords the cursor could possibly be, 
//within the borders of our TB (the exact pos of the next x,y following our string end)
static COORD
calcMaxBoxCursorPos()
{
	COORD coord = { 0,0 };
	
	return coord;
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

	//there could be 2 cases now:
	//1. pressing at an empty (at the end) non written space
	//2. pressing in between letters
	
	//no matter the click {x,y} pos inside the tb, if the tb is empty
	//simply set the current box cursor at start:
	if (_value.empty()) {
		setBoxCursorX(_left + BORDER_OFFSET);
		setBoxCursorY(_top + BORDER_OFFSET);
	}
	else
	{
		COORD max_box_cursor_pos = calcMaxBoxCursorPos();

		//case 1: 
		//user clicked inside the tb borders, but after the text
		if (x > max_box_cursor_pos.X && y > max_box_cursor_pos.Y)
		{

		}

		if (true/*case 2 goes here*/)
		{
			;
		}
	}

	return true;
}

void
TextBox::keyDown(int keyCode, char character)
{
	string s;
	Graphics g;

	s.push_back(character);
	
	switch (keyCode)
	{
	//numpad keys:
	case VK_NUMPAD4:

		return;
	case VK_NUMPAD6:

		return;
	case VK_NUMPAD8:

		return;
	case VK_NUMPAD2:

		return;
	case VK_LEFT:

		return;
	case VK_RIGHT:

		return;
	case VK_UP:

		return;
	case VK_DOWN:

		return;
	case VK_BACK:

		return;
	case VK_DELETE:

		return;

	case VK_SPACE:

		return;
	default:

		break;
	} 

	if (character != NULL)
	{
		_value.push_back(character);
	}
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