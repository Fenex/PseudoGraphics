#include "EventEngine.h"
#include <vector>
#include <algorithm>
using namespace std;

EventEngine::EventEngine(DWORD input, DWORD output)
	: _console(GetStdHandle(input)), _graphics(output)
{
	GetConsoleMode(_console, &_consoleMode);
	SetConsoleMode(_console, ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);
}

void 
EventEngine::run(Control& control)
{
	bool redraw = true;

	while (true)
	{

		if (redraw == true) {
			//init default cursor attributes:
			_graphics.clearScreen();
			_graphics.setCursorVisibility(false);

			//draw EVERY control and child of control on our panel (recursive):
			control.draw(_graphics);
			
			redraw = false;
		}

		INPUT_RECORD record;
		DWORD count;
		ReadConsoleInput(_console, &record, 1, &count);
		switch (record.EventType)
		{
		case KEY_EVENT:
		{
			auto focused_control = Control::getFocus();
			if (focused_control != nullptr && record.Event.KeyEvent.bKeyDown)
			{
				auto code = record.Event.KeyEvent.wVirtualKeyCode;
				auto chr = record.Event.KeyEvent.uChar.AsciiChar;
				if (code == VK_TAB)
					moveFocus(control, focused_control);
				else
					focused_control->keyDown(code, chr);
				//redraw = true;
			}
			break;
		}
		case MOUSE_EVENT:
		{
			auto button = record.Event.MouseEvent.dwButtonState;
			auto coord = record.Event.MouseEvent.dwMousePosition;
			auto x = coord.X - control.getLeft();
			auto y = coord.Y - control.getTop();
			if (button == FROM_LEFT_1ST_BUTTON_PRESSED || button == RIGHTMOST_BUTTON_PRESSED)
			{
				if (control.mousePressed(x, y, button == FROM_LEFT_1ST_BUTTON_PRESSED))
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