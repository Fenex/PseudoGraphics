#pragma once
#include "Control.h"
#include "Button.h"
class ComboBox :
	public Control
{
private:
	//string _options_string_array;
	int _drop_down_menu_width, _drop_down_menu_height;
	int _options_list_size, _max_option_size;
	bool _is_menu_open;
	vector<string> _options_list;
	Button* _menu_down_button;
	Label* _selected_val_label;

	void initChildren();
	int findMaxString(vector<string> options_list);
	void openDropDownMenu();
	void closeDropDownMenu();
	bool findClickedItem(int x, int y);
public:
	//ComboBox();
	ComboBox(short top, short left, vector<string> options_list);
	~ComboBox();
	virtual bool mousePressed(int x, int y, bool isLeft, Graphics& g);
	virtual bool mouseHover(int x, int y, Graphics& g);
	bool myPureFunction() { return false; }

	/*void draw(Graphics&);
	bool myPureFunction() { return false; }
	virtual bool mousePressed(int x, int y, bool isLeft);*/
};

