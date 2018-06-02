#pragma once
#include "Button.h"
class NumericBox : public Control
{
private:
	int _max, _min;
	Button *minButton, *plusButton;
	Label* numericLabel;
	string _value;

	void initChildren(int val);

public:
	NumericBox(int max = MAX_NUMERIC_VAL, int min = MIN_NUMERIC_VAL, int value = DEF_NUMERIC_VAL);
	~NumericBox();
	void draw(Graphics&);
	bool myPureFunction() { return false; }
	void inc();
	void dec();
};

