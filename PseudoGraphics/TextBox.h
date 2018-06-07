#pragma once
#include "Control.h"
class TextBox : public Control
{
	short _box_cursor_x;
	short _box_cursor_y;
	string _value;

	void setBoxCursorX(short x);
	void setBoxCursorY(short y);

public:
	TextBox();
	TextBox(short left, short top, short width, short height);
	~TextBox() {}

	bool myPureFunction();
	void draw(Graphics& g);
	void drawValue(Graphics& g);
	bool mousePressed(int x, int y, bool isLeft, Graphics& g);
	void keyDown(int keyCode, char character, Graphics& g);
	COORD valueEndPos();
	short getBoxCursorX();
	short getBoxCursorY();
};

