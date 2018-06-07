#include "EventEngine.h"
#include "TextBox.h"
#include <vector>
#include <algorithm>
using namespace std;

EventEngine::EventEngine(DWORD input, DWORD output)
	: _console(GetStdHandle(input)), _graphics(output)
{
	GetConsoleMode(_console, &_consoleMode);
	SetConsoleMode(_console, ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);
}

static bool
isATextBox(Control* control) {
	const char* fn = __FUNCTION__;

	if (dynamic_cast<TextBox*>(control) != NULL)
	{
		//debug(PG_DBG_INFO, "%s: focused control is a TextBox.", fn);
		return true;
	}
	return false;
}

static void
setFirstFocusableChild(Control& control)
{
	if (!control.getChildren().empty())
	{
		//if every child can't be focused by definition, defaultly set the 1st one as focused to avoid empty references:
		Control::setFocus(*(control.getChildren().at(0)));

		for (size_t i = 0; i < control.getChildren().size() ; i++)
		{
			if (control.getChildren().at(i)->canGetFocus())
			{
				Control::setFocus(*(control.getChildren().at(i)));
				return;
			}
		}
	}

	return;
	
}

void 
EventEngine::run(Control& control)
{
	char* fn = __FUNCTION__;
	debug(PG_DBG_INFO, "%s: called.", fn);

	bool redraw = true;

	//set 1st child as focused by default
	setFirstFocusableChild(control);
	_graphics.setCursorVisibility(false);

	while (true)
	{
			
		//save last cursor position before we draw. this will help us get to the exact cursor pos
		//we were if we're writing inside of a text box (e.g):
		//COORD last_cur_pos = _graphics.GetConsoleCursorPosition();

		if (redraw == true) {
			_graphics.clearScreen();

			//draw every control and child of control on our panel (recursive):
			control.draw(_graphics);
			redraw = false;
		}
		
		//get back to last cur position:
		//_graphics.moveTo(last_cur_pos.X, last_cur_pos.Y);

		auto focused_control = Control::getFocus();

		//if any TextBox is focused, show cursor and set it to the last coord it was on:
		bool visible = isATextBox(focused_control) ? true : false;
		_graphics.setCursorVisibility(visible);

		INPUT_RECORD record;
		DWORD count;
		ReadConsoleInput(_console, &record, 1, &count);
		switch (record.EventType)
		{
		case KEY_EVENT:
		{
			if (focused_control != nullptr && record.Event.KeyEvent.bKeyDown)
			{
				auto code = record.Event.KeyEvent.wVirtualKeyCode;
				auto chr = record.Event.KeyEvent.uChar.AsciiChar;
				if (code == VK_TAB)
				{
					debug(PG_DBG_INFO, "%s: KEY_EVENT: TAB.", fn);
					moveFocus(control, focused_control);
					
					if (isATextBox(Control::getFocus()))
					{
						//if we tab to a TextBox, place cursor at this text box as if it was clicked:
						_graphics.moveTo(
							(Control::getFocus())->getLeft() + BORDER_OFFSET,
							(Control::getFocus())->getTop() + BORDER_OFFSET);
					}
				}
				else
				{
					debug(PG_DBG_INFO, "%s: KEY_EVENT: Ascii Char.", fn);
					focused_control->keyDown(code, chr, _graphics);
				}
				redraw = true;
			}
			break;
		}
		case MOUSE_EVENT:
		{
			auto button = record.Event.MouseEvent.dwButtonState;
			auto coord = record.Event.MouseEvent.dwMousePosition;
			auto x = coord.X;
			auto y = coord.Y;
			if (button == FROM_LEFT_1ST_BUTTON_PRESSED || button == RIGHTMOST_BUTTON_PRESSED)
			{
				debug(PG_DBG_INFO, "%s: MOUSE_EVENT: at {%d,%d} isLeftClick=%d.", fn, x, y, button == FROM_LEFT_1ST_BUTTON_PRESSED);
				if (control.mousePressed(x, y, button == FROM_LEFT_1ST_BUTTON_PRESSED, _graphics))
				{
					debug(PG_DBG_INFO, "%s: redraw.", fn);
					redraw = true;
				}
			}
			break;
		}
		default:
			break;
		}
	}
}

EventEngine::~EventEngine()
{
	SetConsoleMode(_console, _consoleMode);
}

//this function iterates (circular) over the children of the control, looking for the to-be-focused child:
void 
EventEngine::moveFocus(Control &main, Control *focused) 
{
	vector<Control*> controls = main.getChildren();
	//old: main.getAllControls(&controls);

	//set iterator for the children list:
	auto iter = find(controls.begin(), controls.end(), focused);
	
	//iterate untill iterator == the to-be-focused child:
	do
		if (++iter == controls.end())
			iter = controls.begin();
	while (!(*iter)->canGetFocus());

	Control::setFocus(**iter);
}