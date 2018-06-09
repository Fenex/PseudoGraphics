#pragma once
#ifndef BUTTON_H
#define BUTTON_H

#include "Label.h"

class NumericBox;	//forward declaration to include NumericBox in typedef function

typedef void (*OnButtonClicked) (NumericBox* , int, int);

class Button : public Label
{

public:
	OnButtonClicked clickFunc;

	//methods
	Button();
	Button(string& s);
	Button(const char* s);
	virtual ~Button();
	virtual bool myPureFunction();
	bool mousePressed(int x, int y, bool isLeft, Graphics& g);
	void fixDimensions();
};

#endif // !BUTTON_H
