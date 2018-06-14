#pragma once
#include "Button.h"
class PgList : public Control
{
	bool _multiple_choices;

public:
	PgList();
	~PgList();

	virtual void draw(Graphics& g);
	virtual bool mousePressed(int x, int y, bool isLeft, Graphics& g);
	virtual void keyDown(int keyCode, char character, Graphics& g) ;
	virtual bool addItem(string item);
	virtual bool removeSelectedItem();	string getSelectedItemValue();	int getSelectedItemPos();	int clickedChildIndex(const short x, const short y);	bool isMouseOnSelectedItem(const short x, const short y);
	bool isValidIndex(int idx);
	Button* getChildAt(int pos);
	Button* initButton(string value);
	void setSelectedItem(const int pos, char symbol);	void clearSelection();
	void flipColorsAt(int item_pos);

	void add(Control* child) {} //use addItem instead
	bool myPureFunction() { return true; }

};

