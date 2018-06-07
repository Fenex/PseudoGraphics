#include "TextBox.h"
#include <math.h>

TextBox::TextBox()
{
	setClickable(true);
	setFocusable(true);
	setFrameType(SINGLE_SOLID);
}

TextBox::TextBox(short left = 0, short top = 0, short width = 5, short height = 5) : Control()
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
	drawValue(g);
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

//this func returns the maximum x,y coords the cursor could possibly be, 
//within the borders of our TB (the exact pos of the next x,y following our string end)
COORD
TextBox::valueEndPos()
{
	char* fn = __FUNCTION__;
	debug(PG_DBG_INFO, "%s called.", fn);

	short exact_cols_size = getWidth() - (BORDER_OFFSET * 2);
	short max_x, max_y;

	debug(PG_DBG_INFO, "%s left=%d  top=%d", fn, _left, _top);
	debug(PG_DBG_INFO, "%s _value.size()=%d", fn, _value.size());
	debug(PG_DBG_INFO, "%s exact_cols_size=%d", fn, exact_cols_size);
	debug(PG_DBG_INFO, "%s ceil(%f / %f)=%f", fn, (double)_value.size(), (double)exact_cols_size, ceil((double)_value.size() / (double)exact_cols_size));

	if ((_value.size() % exact_cols_size) == 0 )
	{
		max_x = getLeft() + _value.size();
	}
	else
	{
		max_x = getLeft() + (_value.size() % exact_cols_size);
	}

	max_y = getTop() + BORDER_OFFSET + ceil(_value.size() / exact_cols_size);

	debug(PG_DBG_INFO, "%s {max_x,max_y} ={%d,%d}.", fn, max_x, max_y);

	return { max_x, max_y };
}

bool
TextBox::mousePressed(int x, int y, bool isLeft, Graphics& g)
{
	char* fn = __FUNCTION__;
	debug(PG_DBG_INFO, "%s called.", fn );

	g.setCursorVisibility(true);
	g.setBackground(_background);
	g.setForeground(_foreground);
	
	//there could be 2 cases now:
	//1. pressing at an empty (at the end) non written space
	//2. pressing in between letters

	if (_value.empty()) {
		g.moveTo(getLeft()+BORDER_OFFSET, getTop()+BORDER_OFFSET);
	}
	else
	{	
		//case 1:
		if (y >= valueEndPos().Y && x >= valueEndPos().X || 
			y > valueEndPos().Y)
		{
			if (valueEndPos().X == getLeft() + getWidth() - BORDER_OFFSET*2)
			{
				g.moveTo(getLeft() + 1, valueEndPos().Y);
			}
			else
			{
				g.moveTo(valueEndPos().X+1, valueEndPos().Y);
			}
		}
		//case 2:
		else
		{	
			g.moveTo(x, y);
		}
	}
	return true;
}

void
TextBox::keyDown(int keyCode, char character, Graphics& g)
{
	char* fn = __FUNCTION__;

	string s;

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

	//simple matrix area calculation:
	int MAX_TEXT_LENGTH_IN_BOX = (getWidth() - BORDER_OFFSET * 2) * (getHeight() - BORDER_OFFSET * 2);

	if (character != NULL)
	{
		if (_value.size() >= MAX_TEXT_LENGTH_IN_BOX)
		{
			return;
		}

		_value.push_back(character);
		short line_down = 0;
		short roll_back = 0;
		if (g.GetConsoleCursorPosition().X == getLeft() + getWidth() - BORDER_OFFSET*2)
		{
			line_down++;
			roll_back = getWidth() - BORDER_OFFSET * 2;
		}
		g.moveTo(g.GetConsoleCursorPosition().X + 1 - roll_back, g.GetConsoleCursorPosition().Y + line_down);
	}
}


void
TextBox::drawValue(Graphics& g)
{
	short exact_row_size = getWidth() - (BORDER_OFFSET * 2);
	short exact_col_size = getHeight() - (BORDER_OFFSET * 2);;

	g.moveTo(getLeft() + BORDER_OFFSET, getTop() + BORDER_OFFSET);

	for (short i = 0, j = 0; i < _value.size(); i++)
	{
		//if we reached maximum box 
		if (i == exact_col_size * exact_row_size)
		{
			return;
		}

		if (((i != 0) && (i % exact_row_size)) == 0)
		{
			g.moveTo(_left + 1, (_top + BORDER_OFFSET) + (j++));	
		}

		string temp_str;
		temp_str.push_back(_value.at(i));
		g.write(temp_str);
	}

}

bool 
TextBox::myPureFunction()
{
	return true;
}