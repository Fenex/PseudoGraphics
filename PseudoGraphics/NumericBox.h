#pragma once
#include "Button.h"
class NumericBox : public Control
{
private:
	int _max, _min;
	Button *_min_button, *_plus_button;
	Label* numeric_label;
	int _value;

	void initChildren(int val);
	void inc();
	void dec();
public:
	NumericBox(short top, short left, int max = MAX_NUMERIC_VAL, int min = MIN_NUMERIC_VAL, int value = DEF_NUMERIC_VAL);
	~NumericBox();
	void draw(Graphics&);
	bool myPureFunction() { return false; }
	virtual bool mousePressed(int x, int y, bool isLeft);
	int getValue() { return _value; }

};



