#ifndef LABEL_H
#define LABEL_H

#include "Control.h"
#include <iostream>
#include <string>

using namespace std;

class Label: public Control
{   
	private:
		string value;
  public:
		Label();
		Label(string);
		string getValue();
		void setValue(string);
		void draw(Graphics& g, int x, int y, size_t z);
		void draw(Graphics& g);
		bool myPureFunction();
};

#endif // !LABEL_H