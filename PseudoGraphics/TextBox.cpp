#include "TextBox.h"
#include <math.h>

TextBox::TextBox()
{
	setClickable(true);
	setFocusable(true);
	setFrameType(SINGLE_SOLID);
	setLastPos({ _left + BORDER_OFFSET, _top + BORDER_OFFSET });
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
	setLastPos({ _left + BORDER_OFFSET, _top + BORDER_OFFSET });
}

//draw the entire text box
void
TextBox::draw(Graphics& g) {
	char* fn = __FUNCTION__;
	Control::draw(g);
	drawValue(g);
}

//this func returns the maximum x,y coords the cursor could possibly be, 
//within the borders of our TB (the exact pos of the next x,y following our string end)
COORD
TextBox::valueEndPos()
{
	char* fn = __FUNCTION__;

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
		COORD end_str_pos = valueEndPos();

		//case 1:
		if (y >= end_str_pos.Y && x >= end_str_pos.X ||
			y > end_str_pos.Y)
		{
			debug(PG_DBG_INFO, "%s clicked outside text.", fn);
			if (end_str_pos.X == getLeft() + getWidth() - BORDER_OFFSET*2)
			{
				setLastPos({getLeft() + 1, end_str_pos.Y});
				//g.moveTo(getLeft() + 1, end_str_pos.Y);
			}
			else
			{
				setLastPos({end_str_pos.X + 1, end_str_pos.Y });
				//g.moveTo(end_str_pos.X+1, end_str_pos.Y);
			}
		}
		else
		{
			//case 2:
			//g.moveTo(x, y);
			debug(PG_DBG_INFO, "%s clicked between text.", fn);
			setLastPos({(short)x, (short)y});
		}
	}
	return true;
}

void
TextBox::keyDown(int keyCode, char character, Graphics& g)
{
	char* fn = __FUNCTION__;


	string s;
	COORD c_pos = g.GetConsoleCursorPosition();
	s.push_back(character);
	
	switch (keyCode)
	{
	//numpad keys:
	case VK_NUMPAD4:
	case VK_LEFT:
		if (!(c_pos.X - 1 == getLeft() + BORDER_OFFSET))
			setLastPos({ c_pos.X - 1, c_pos.Y });
		return;
	case VK_NUMPAD6:
	case VK_RIGHT:
		if (!(c_pos.X + 1 == getLeft() + getWidth() - BORDER_OFFSET))
			setLastPos({c_pos.X + 1, c_pos.Y});
		return;
	case VK_NUMPAD8:
	case VK_UP:
		if (!(c_pos.Y - 1 == getTop() + BORDER_OFFSET))
			setLastPos({ c_pos.X, c_pos.Y - 1 });
		return;
	case VK_NUMPAD2:
	case VK_DOWN:
		if (!(c_pos.Y + 1 == getTop() + getHeight()  - BORDER_OFFSET))
			setLastPos({ c_pos.X, c_pos.Y + 1 });
		return;

	case VK_BACK:

		return;
	case VK_DELETE:

		return;

	case VK_SPACE:
		break;

	case VK_RETURN:

		return;

	default:

		break;
	} 

	//simple matrix area calculation:
	int MAX_TEXT_LENGTH_IN_BOX = (getWidth() - BORDER_OFFSET * 2) * (getHeight() - BORDER_OFFSET * 2);

	if (character != NULL)
	{
		if (_value.size() < MAX_TEXT_LENGTH_IN_BOX)
		{
			_value.push_back(character);
			if (getLastPos().X + 1 == getLeft() + getWidth() - BORDER_OFFSET && getLastPos().Y < getTop() + getHeight() - BORDER_OFFSET )
			{
				setLastPos({ getLeft() + BORDER_OFFSET, getLastPos().Y + 1});
			}
			else
			{
				setLastPos({ getLastPos().X + 1 , getLastPos().Y});
			}
		}
	}
}


void
TextBox::drawValue(Graphics& g)
{
	short exact_row_size = getWidth() - (BORDER_OFFSET * 2);
	short exact_col_size = getHeight() - (BORDER_OFFSET * 2);;

	//setLastPos({ g.GetConsoleCursorPosition().X, g.GetConsoleCursorPosition().Y });
	
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

COORD
TextBox::getLastPos()
{
	return _last_pos;
}

void
TextBox::setLastPos(COORD pos)
{
	_last_pos = pos;
}



bool 
TextBox::myPureFunction()
{
	return true;
}
