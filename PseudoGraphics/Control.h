#pragma once
#ifndef CONTROLS_H
#define CONTROLS_H

#include "Graphics.h"
#include "Constants.h"
#include <vector>

using namespace std;

typedef enum {
	PG_DBG_INFO,
	PG_DBG_ERROR
}DebugLevel;

typedef enum {
	NONE,
	SINGLE_SOLID,
	DOUBLE_SOLID
}FrameType;

class Control {

protected:
	short left;
	short top;
	vector<Control*> chidren;

public:
	Control();
	static Control* getFocus() { return NULL; };
	static void setFocus(Control& control) {};
	
	virtual void draw(Graphics& g, int x, int y, size_t z) {};
	virtual void mousePressed(int x, int y, bool isLeft) {};
	virtual void keyDown(int keyCode, char charecter) {};
	virtual short getLeft() { return 0; };
	virtual short getTop() { return 0; };
	virtual void getAllControls(vector<Control*>* controls) {};
	virtual bool canGetFocus() { return FALSE; };
	virtual bool myPureFunction() = 0;

	~Control();
};

#endif // !CONTROLS_H