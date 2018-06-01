#pragma once
#include "Button.h"
class NumericBox : public Button
{
private:
	int _max, _min;
	string _value;

public:
	NumericBox();
	NumericBox(int max, int min, string value);
	~NumericBox();
	bool myPureFunction() {};
	void inc();
	void dec();
};

