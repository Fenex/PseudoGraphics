#pragma once
#include "Control.h"
class TextBox :
	public Control
{
protected:
	CONSOLE_SCREEN_BUFFER_INFO _cursor;
	COORD _coord, _dim;
	HANDLE _in, _out;
public:
	TextBox(COORD coord = { 0,0 }, COORD dim = { 0,0 });
	~TextBox() {}

	void setBackground(DWORD);
	void draw();
	void innerDraw(char, char, char);
	void handleInput();
};

