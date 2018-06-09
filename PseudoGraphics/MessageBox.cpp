#pragma once
#include "MessageBox.h"
#include "Button.h"

//TODO:	1. update MessageBox width & height after pop up is closed. 
//		2. align pop location relative to button
//		3. set MessageBox width to fit max size of content

MyMessageBox::MyMessageBox(short top, short left,string popUpButtonText, string popUpMessage)
{
	char* fn = __FUNCTION__;
	_is_pop_up_open = false;
	_top = top;
	_left = left;
	_pop_up_message = popUpMessage;
	_open_pop_up_button_text = popUpButtonText;
	_is_confirmed = false;
	debug(PG_DBG_INFO, "%s: called. %d: leftInit", fn, _left);
	initSize();
	initButtons();
}

MyMessageBox::~MyMessageBox()
{
}

void
MyMessageBox::initButtons()
{
	char* fn = __FUNCTION__;
	add(_open_pop_up_button = new Button(_open_pop_up_button_text));
	debug(PG_DBG_INFO, "%s: called. %d: width", fn, _open_pop_up_button->getWidth());
	_open_pop_up_button->setTop(_top);
	_open_pop_up_button->setLeft(_left);
	_open_pop_up_button->setColor(Color::Black, Color::Red);
}

void 
MyMessageBox::initSize()
{
	_height = ONE_CHAR_BUTTON_HEIGHT;
	_width = NUMERIC_BOX_LABEL_SPACE_MARGIN + _open_pop_up_button_text.size();	// initialy - box is not displayed so initial width is calculated as the width of the button
}


void
MyMessageBox::draw(Graphics& g)
{
	Control::draw(g);
}

bool
MyMessageBox::mousePressed(int x, int y, bool isLeft, Graphics& g)
{
	
	if (isInside(x, y, _open_pop_up_button->getLeft(), _open_pop_up_button->getTop(), _open_pop_up_button->getWidth(), _open_pop_up_button->getHeight()) && !_is_pop_up_open) {
		openPopUp();
		return true;
	}
	else if (isInside(x, y, _confirm_button->getLeft(), _confirm_button->getTop(), _confirm_button->getWidth(), _confirm_button->getHeight()) && _is_pop_up_open) {
		_is_confirmed = true;
		closePopUp();
		return true;
	}
	else if (isInside(x, y, _cancel_button->getLeft(), _cancel_button->getTop(), _cancel_button->getWidth(), _cancel_button->getHeight()) && _is_pop_up_open) {
		_is_confirmed = false;
		closePopUp();
		return true;
	}
	return false;
}

void
MyMessageBox::openPopUp()
{
	_is_pop_up_open = true;
	//update width\height and set position
	_height = MESSAGE_BOX_DEFAULT_HEIGHT;
	_width = MAX(NUMERIC_BOX_LABEL_SPACE_MARGIN + _open_pop_up_button_text.size(), MIN_MSESSAGE_BOX_WIDTH);
	_top -= MESSAGE_BOX_TOP_OFFSET;
	_left += ((_open_pop_up_button_text.size()+NUMERIC_BOX_LABEL_SPACE_MARGIN)/2 - (_width)/2 );
	//display label and buttons
	add(_pop_up_message_label = new Label(_pop_up_message));
	_pop_up_message_label->setTop(_top);
	_pop_up_message_label->setLeft(_left);
	_pop_up_message_label->setColor(Color::Black, Color::Red);
	_pop_up_message_label->setFrameType(SINGLE_SOLID);
	_pop_up_message_label->setWidth(_width);
	_pop_up_message_label->setHeight(_height - ONE_CHAR_BUTTON_HEIGHT);
	
	add(_confirm_button = new Button(DEFAULT_CONFIRM_BUTTON_TEXT));
	_confirm_button->setTop(_pop_up_message_label->getTop() + ONE_CHAR_BUTTON_HEIGHT);
	_confirm_button->setLeft(_pop_up_message_label->getLeft() + 0.2*_width + NUMERIC_BOX_LABEL_SPACE_MARGIN);
	_confirm_button->setColor(Color::Black, Color::Red);

	add(_cancel_button = new Button(DEFAULT_CANCEL_BUTTON_TEXT));
	_cancel_button->setTop(_pop_up_message_label->getTop() + ONE_CHAR_BUTTON_HEIGHT);
	_cancel_button->setLeft(_confirm_button->getLeft() + _confirm_button->getWidth() + NUMERIC_BOX_LABEL_SPACE_MARGIN);
	_cancel_button->setColor(Color::Black, Color::Red);
}

void
MyMessageBox::closePopUp()
{
	char* fn = __FUNCTION__;
	_is_pop_up_open = false;
	//remove all children except pop up window open button
	_children.erase(_children.begin() + 1, _children.end());
	//restore initial width, height and position
	_top +=  MESSAGE_BOX_TOP_OFFSET;
	_left -= ((_open_pop_up_button_text.size() + NUMERIC_BOX_LABEL_SPACE_MARGIN) / 2 - (_width) / 2);
	initSize();

	debug(PG_DBG_INFO, "%s: ended. %s: bool", fn, _is_confirmed ? "true" : "false");
	debug(PG_DBG_INFO, "%s: ended. %d: _top	%d: _left", fn, _top, _left);
}
