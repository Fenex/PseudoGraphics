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

#define MAX(X, Y) ( (X) > (Y) ? (X) : (Y))

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

	static Control* _focused_control;
	//todo: hange convension here. underscore_ before var name is only for private members:
protected:
	short _left, _top;
	short _width, _height;
	bool _focusable;
	bool _clickable;
	bool _is_flipped;
	FrameType _frame_type;
	Control *_other;	//enable a component to refrence another by setting a pointer to it using setter. default is NULL
	vector<Control*> _children;
	Color _background, _foreground;
	

public:
	Control();
	static Control* getFocus();
	static void setFocus(Control& control);
	
	//virtual void draw(Graphics& g, int x, int y, size_t z);
	virtual void draw(Graphics& g);
	//virtual bool mouseHover(int x, int y, Graphics& g);
	virtual bool mousePressed(int x, int y, bool isLeft, Graphics& g);
	virtual void keyDown(int keyCode, char character, Graphics& g) {};
	virtual short getLeft() { return _left; };
	virtual short getTop() { return _top; };
	virtual void getAllControls(vector<Control*>* controls);
	virtual bool canGetFocus();
	virtual bool canBeClicked();
	virtual string getStringValue() { return ""; };
	virtual bool myPureFunction() = 0;

	virtual void drawBorder(Graphics& g);
	virtual void drawChildren(Graphics& g);
	virtual void drawLine(char, char, char);
	vector<Control*> getChildren();
	void setFrameType(FrameType frame_type);
	FrameType getFrameType();
	void setColor(Color bg, Color fg);
	bool isFlipped() { return _is_flipped; }
	short getWidth();
	short getHeight();
	Color getForeground() { return _foreground; }
	Color getBackground() { return _background; }
	void flipColor();
	virtual void setTop(short x);
	virtual void setLeft(short y);
	void setWidth(short x);
	void setHeight(short y);
	void setOtherComponent(Control *other);
	void add(Control* child);
	void setClickable(bool clickable);
	void setFocusable(bool focusable);


	~Control();
};

void debug(DebugLevel lvl, const char *format, ...);

#endif // !CONTROLS_H