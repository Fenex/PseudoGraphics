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
		//todo: replace this first 'if' with isInTextBoundaries() call:
		if (y >= end_str_pos.Y && x >= end_str_pos.X ||
			y > end_str_pos.Y)
		{
			debug(PG_DBG_INFO, "%s clicked outside text.", fn);
			if (end_str_pos.X == getLeft() + getWidth() - BORDER_OFFSET*2)
			{
				setLastPos({getLeft() + 1, end_str_pos.Y});
			}
			else
			{
				setLastPos({end_str_pos.X + 1, end_str_pos.Y });
			}
		}
		else
		{
			//case 2:
			debug(PG_DBG_INFO, "%s clicked between text.", fn);
			setLastPos({(short)x, (short)y});
		}
	}
	return true;
}

static bool
isInTextBoundaries(COORD max_pos, COORD new_pos)
{
	if (new_pos.Y >= max_pos.Y && new_pos.X-1 > max_pos.X ||
		new_pos.Y > max_pos.Y)
	{
		return false;
	}
	return true;
}

bool
TextBox::isValidMove(int key_code, Graphics& g)
{
	COORD cur_pos = g.GetConsoleCursorPosition();
	COORD end_str_pos = valueEndPos();
	COORD new_pos;

	switch (key_code)
	{

		case VK_LEFT:
			new_pos = { cur_pos.X - 1 , cur_pos.Y};
			return new_pos.X > getLeft() && isInTextBoundaries(end_str_pos, new_pos);

		case VK_RIGHT:
			new_pos = { cur_pos.X + 1 , cur_pos.Y };
			return new_pos.X < getLeft() + getWidth() - BORDER_OFFSET && isInTextBoundaries(end_str_pos, new_pos);

		case VK_UP:
			new_pos = { cur_pos.X, cur_pos.Y - 1 };
			return new_pos.Y > getTop() && isInTextBoundaries(end_str_pos, new_pos);

		case VK_DOWN:
			new_pos = { cur_pos.X, cur_pos.Y + 1 };
			return new_pos.Y < getTop() + getHeight() - BORDER_OFFSET && isInTextBoundaries(end_str_pos, new_pos);

		default:
			break;
	}

	return false;
}

void
TextBox::handleBackspace(COORD curr_pos)
{
	int idx = posToIndex(curr_pos);

	if (idx != -1)
	{
		//if we are next to the left border of the tb
		if (idx % (getWidth() - (BORDER_OFFSET * 2)) == 0)
		{
			//if we are the top left corner
			if (idx == 0)
			{
				//nothing to delte backwards, leave.
				return;
			}
			//we are at the 2nd and below line - its safe to delete.
			else
			{
				setLastPos({ getLeft() + getWidth() - (BORDER_OFFSET * 2), getLastPos().Y - 1 });
			}
		}
		//we are at the end of the text or in between:
		else
		{
			setLastPos({ getLastPos().X - 1, getLastPos().Y });
		}
		//place iterator at previous position to the cursor, and erase char:
		auto itr = _value.begin() + idx - 1;
		_value.erase(itr);
	}
	return;
}

void
TextBox::handleDelete(COORD curr_pos)
{
	char* fn = __FUNCTION__;
	int idx = posToIndex(curr_pos);
	debug(PG_DBG_ERROR, "%s idx=%d.", fn);

	if (idx != -1)
	{
		//if we are next to the right border of the tb
		if (curr_pos.X + 1 == getLeft() + getWidth())
		{
			return;
			//if we are at the bottom right corner
			if (curr_pos.Y == (getTop() + getWidth() - BORDER_OFFSET))
			{
				//nothing to delte forwards, leave.
				return;
			}
		}
		setLastPos(curr_pos);
		//place iterator at previous position to the cursor, and erase char:
		auto itr = _value.begin() + idx;
		_value.erase(itr);
	}
	return;
}

void
TextBox::keyDown(int keyCode, char character, Graphics& g)
{
	char* fn = __FUNCTION__;
	
	COORD c_pos = g.GetConsoleCursorPosition();
	int idx = posToIndex(c_pos);
	
	switch (keyCode)
	{
	//numpad keys:
	case VK_NUMPAD4:
	case VK_LEFT:
		if (isValidMove(VK_LEFT, g))
			setLastPos({ c_pos.X - 1, c_pos.Y });
		return;
	case VK_NUMPAD6:
	case VK_RIGHT:
		if (isValidMove(VK_RIGHT, g))
			setLastPos({ c_pos.X + 1, c_pos.Y });
			
		return;
	case VK_NUMPAD8:
	case VK_UP:
		if (isValidMove(VK_UP, g))
			setLastPos({ c_pos.X, c_pos.Y - 1 });
		return;
	case VK_NUMPAD2:
	case VK_DOWN:
		if (isValidMove(VK_DOWN, g))
			setLastPos({ c_pos.X, c_pos.Y + 1 });
		return;

	case VK_BACK:
		return handleBackspace(c_pos);
	case VK_DELETE:
		return handleDelete(c_pos);

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

			if (idx != -1)
			{
				//push at the end
				if (idx == _value.size())
				{
					_value.push_back(character);
				}
				else
				{
					//push in the middle of the text || push at start:
					auto itr = _value.begin() + idx;
					_value.insert(itr, character);

					//if cursor is in between the text, dont move it
					return;
				}
			}
			else
			{
				debug(PG_DBG_ERROR, "%s invalid index. do nothing.", fn);
				return;
			}
			

			//set the curosr to next X position and go down a line if needed:
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

//this function converts the cursor pos into the correct char index in text (_value):
int
TextBox::posToIndex(COORD pos)
{
	char* fn = __FUNCTION__;

	int exact_row_size = getWidth() - (BORDER_OFFSET * 2);
	int lines = pos.Y - getTop() - BORDER_OFFSET;
	int idx = pos.X - getLeft() - BORDER_OFFSET + (lines * exact_row_size);

	debug(PG_DBG_INFO, "%s idx =%d", fn, idx);
	return (idx > _value.size() || idx < 0)  ?  -1 : idx;

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
