#pragma once
#ifndef CONTROLS_H
#define CONTROLS_H

#include "Graphics.h"
#include "Constants.h"
#include <memory>
#include <ctime>
#include <vector>
#include <fstream>
#include <iostream>

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
	short _dim_x, _dim_y;
	FrameType _frame_type;
	vector<Control*> _children;
	Color _background, _foreground;

public:
	Control();
	static Control* getFocus() { return NULL; };
	static void setFocus(Control& control) {};
	
	//virtual void draw(Graphics& g, int x, int y, size_t z);
	virtual void draw(Graphics& g);
	virtual void mousePressed(int x, int y, bool isLeft) {};
	virtual void keyDown(int keyCode, char charecter) {};
	virtual short getLeft() { return 0; };
	virtual short getTop() { return 0; };
	virtual void getAllControls(vector<Control*>* controls) {};
	virtual bool canGetFocus() { return FALSE; };
	virtual bool myPureFunction() = 0;

	virtual void drawBorder(Graphics& g);
	virtual void drawChildren(Graphics& g);
	virtual void drawLine(char, char, char);
	vector<Control*> getChildren();

	~Control();
};

void debug(DebugLevel lvl, const char *format, ...);

#endif // !CONTROLS_H