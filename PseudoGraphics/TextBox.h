#pragma once
#include "Control.h"
class TextBox : public Control
{
	string _value;
public:
	TextBox();
	TextBox(short left, short top, short width, short height);
	~TextBox() {}

	bool myPureFunction();
	void draw(Graphics& g);
	bool mousePressed(int x, int y, bool isLeft);
};

