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


	while (true)
	{
		_graphics.setCursorVisibility(false);

		if (redraw == true) {


			//draw every control and child of control on our panel (recursive):
			_graphics.clearScreen();
			control.draw(_graphics);
			redraw = false;
		}
		
		auto focused_control = Control::getFocus();

		//if any TextBox is focused, show cursor and set it to the last coord it was on:
		if (isATextBox(focused_control))
		{
			_graphics.setCursorVisibility(true);
			//debug(PG_DBG_INFO, "%s: tb is focused. moving to {%d,%d}", fn, static_cast<TextBox*>(Control::getFocus())->getLastPos().X, static_cast<TextBox*>(Control::getFocus())->getLastPos().Y);
			_graphics.moveTo(
				static_cast<TextBox*>(Control::getFocus())->getLastPos().X,
				static_cast<TextBox*>(Control::getFocus())->getLastPos().Y);
		}
		else
		{
			_graphics.setCursorVisibility(false);
		}

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
					moveFocus(control, focused_control);
				}
				else
				{
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
				debug(PG_DBG_INFO, "%s: MOUSE_CLICKED: at {%d,%d} isLeftClick=%d.", fn, x, y, button == FROM_LEFT_1ST_BUTTON_PRESSED);
				if (control.mousePressed(x, y, button == FROM_LEFT_1ST_BUTTON_PRESSED, _graphics))
				{
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

	//set iterator for the children list:
	auto iter = find(controls.begin(), controls.end(), focused);

	//TODO: add inner iteration (recursive) in case a panel holds ANOTHER panel inside. 
	
	//iterate untill iterator == the to-be-focused child:
	do
		if (++iter == controls.end())
			iter = controls.begin();
	while (!(*iter)->canGetFocus());

	Control::setFocus(**iter);
}