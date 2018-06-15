#include "ComboBox.h"



//TODO: add addItem option to class
ComboBox::ComboBox(short top, short left,vector<string> options_list)
{
	_is_menu_open = false;
	_top = top;
	_left = left;
	_options_list = options_list;
	_options_list_size = _options_list.size();
	_max_option_size = findMaxString(_options_list);
	_width = ONE_CHAR_BUTTON_WIDTH + _max_option_size + NUMERIC_BOX_LABEL_SPACE_MARGIN;	
	_height = ONE_CHAR_BUTTON_HEIGHT;
	initChildren();

	setFrameType(SINGLE_SOLID);
}

ComboBox::~ComboBox()
{
}


int
ComboBox::findMaxString(vector<string> options_list)
{
	int max_string_size = 0;
	for each(string str in options_list) {
		if (str.size() > max_string_size)
			max_string_size = str.size();
	}
	return max_string_size;
}

void 
ComboBox::closeDropDownMenu()
{
	//remove options from display
	_children.erase(_children.begin() + 2, _children.end());
	//update 
	_height -= ONE_CHAR_BUTTON_HEIGHT * _options_list.size();
	_is_menu_open = false;
}


void 
ComboBox::openDropDownMenu()
{
	
	Button *btn_ptr = 0;
	//add menu buttons to children. _chilren[0] & _children[1] are occupied by drop drop button and label
	for (int i = 0, j=1 ; i < _options_list.size(); ++i, ++j) {
		add(btn_ptr = new Button(_options_list[i]));
		btn_ptr->setLeft(_left);
		btn_ptr->setTop(_children[j]->getTop() + ONE_CHAR_BUTTON_HEIGHT);
		btn_ptr->setWidth(_width);
		btn_ptr->setColor(Color::Black, Color::Orange);
	}
	//update box's dimension to fit menu size
	_height +=  ONE_CHAR_BUTTON_HEIGHT * _options_list.size();
	_is_menu_open = true;

}


string
getDashedString(int size)
{
	string s;
	for (int i = 0; i < size; ++i) {
		s.push_back('-');
	}

	return s;
}


void ComboBox::initChildren()
{
	//add dropdown button
	add(_menu_down_button = new Button("V"));
	_menu_down_button->setTop(_top);
	_menu_down_button->setLeft(_left);
	_menu_down_button->setColor(Color::Black, Color::Orange);

	//add selected value label
	add(_selected_val_label = new Label(getDashedString(_max_option_size)));
	_selected_val_label->setTop(_top);
	_selected_val_label->setLeft(_left + ONE_CHAR_BUTTON_WIDTH);
	_selected_val_label->setHeight(5);
	// _selected_val_label->setFrameType(FRA)
	_selected_val_label->setColor(Color::Black, Color::Orange);

	Label *ptr = _selected_val_label;
	char* fn = __FUNCTION__;
	debug(PG_DBG_INFO, "%s: ended. %d: val->geteight", fn, ptr->getHeight());
	

}


bool 
ComboBox::findClickedItem(int x, int y)
{
	for (int i = 2; i < _children.size(); ++i) {
		if (isInside(x, y, _children[i]->getLeft(), _children[i]->getTop(), _children[i]->getWidth(), _children[i]->getHeight())) {
			_selected_val_label->setValue(_children[i]->getStringValue());
			return true;
		}
	}
	return false;
}

bool 
ComboBox::mousePressed(int x, int y, bool isLeft, Graphics& g)
{
	Button *item_button_ptr;
	bool item_clicked = false;

	if (!_is_menu_open) {
		if (isInside(x, y, _menu_down_button->getLeft(), _menu_down_button->getTop(), _menu_down_button->getWidth(), _menu_down_button->getHeight())) {
			openDropDownMenu();
			return true;
		}
	}
	if (_is_menu_open) {
		if (isInside(x, y, _menu_down_button->getLeft(), _menu_down_button->getTop(), _menu_down_button->getWidth(), _menu_down_button->getHeight())) {
			closeDropDownMenu();
			return true;
		}
		item_clicked = findClickedItem(x,y);
		if (item_clicked) closeDropDownMenu();
		return item_clicked;
	}
	return false;
}

bool 
ComboBox::mouseHover(int x, int y, Graphics & g)
{
	char* fn = __FUNCTION__;
	debug(PG_DBG_INFO, "%s: called.", fn);
	if (_is_menu_open) {
		for (int i = 2; i < _children.size(); ++i) {
			if (isInside(x, y, _children[i]->getLeft(), _children[i]->getTop(), _children[i]->getWidth(), _children[i]->getHeight())) {
				_children[i]->flipColor();
				return true;
			}
		}
		return false;
	}
	return false;
}


