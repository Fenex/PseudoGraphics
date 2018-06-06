#pragma once
#include "MessageBox.h"
#include "Button.h"

//TODO:	1. update MessageBox width & height after pop up is closed. 
//		2. align pop location relative to button
//		3. set MessageBox width to fit max size of content

MyMessageBox::MyMessageBox(string popUpButtonText, string popUpMessage)
{
	char* fn = __FUNCTION__;

	_popUpMessage = popUpMessage;
	_openPopUpButtonText = popUpButtonText;
	_isConfirmed = false;
	debug(PG_DBG_INFO, "%s: called. %s: popUpButtonString", fn, _openPopUpButtonText.c_str());
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
	add(_openPopUpButton = new Button(_openPopUpButtonText));
	debug(PG_DBG_INFO, "%s: called. %d: width", fn, _openPopUpButton->getWidth());
	_openPopUpButton->setTop(_top);
	_openPopUpButton->setLeft(_left);
	_openPopUpButton->setColor(Color::Black, Color::Red);
}

void 
MyMessageBox::initSize()
{
	_height = ONE_CHAR_BUTTON_HEIGHT;
	_width = NUMERIC_BOX_LABEL_SPACE_MARGIN + _openPopUpButtonText.size();	// initialy - box is not displayed so initial width is calculated as the width of the button
}


void
MyMessageBox::draw(Graphics& g)
{
	Control::draw(g);
}

bool
MyMessageBox::mousePressed(int x, int y, bool isLeft)
{
	if (isInside(x, y, _openPopUpButton->getLeft(), _openPopUpButton->getTop(), _openPopUpButton->getWidth(), _openPopUpButton->getHeight())) {
		openPopUp();
		return true;
	}
	else if (isInside(x, y, _confirmButton->getLeft(), _confirmButton->getTop(), _confirmButton->getWidth(), _confirmButton->getHeight())) {
		_isConfirmed = true;
		closePopUp();
		return true;
	}
	else if (isInside(x, y, _cancelButton->getLeft(), _cancelButton->getTop(), _cancelButton->getWidth(), _cancelButton->getHeight())) {
		_isConfirmed = false;
		closePopUp();
		return true;
	}
	return false;
}

void
MyMessageBox::openPopUp()
{
	//update width & height
	_height = MESSAGE_BOX_DEFAULT_HEIGHT;
	_width = MAX(NUMERIC_BOX_LABEL_SPACE_MARGIN + _openPopUpButtonText.size(), MIN_MSESSAGE_BOX_WIDTH);
	_top -= _height;
	_left -= MESSAGE_BOX_LEFT_OFFSET;
	//display label and buttons
	add(_popUpMessageLabel = new Label(_popUpMessage));
	_popUpMessageLabel->setTop(_top);
	_popUpMessageLabel->setLeft(_left);
	_popUpMessageLabel->setColor(Color::Black, Color::Red);
	_popUpMessageLabel->setFrameType(SINGLE_SOLID);
	_popUpMessageLabel->setWidth(_width);
	_popUpMessageLabel->setHeight(_height - ONE_CHAR_BUTTON_HEIGHT);
	
	add(_confirmButton = new Button(DEFAULT_CONFIRM_BUTTON_TEXT));
	_confirmButton->setTop(_popUpMessageLabel->getTop() + ONE_CHAR_BUTTON_HEIGHT);
	_confirmButton->setLeft(_popUpMessageLabel->getLeft() + 0.2*_width + NUMERIC_BOX_LABEL_SPACE_MARGIN);
	_confirmButton->setColor(Color::Black, Color::Red);

	add(_cancelButton = new Button(DEFAULT_CANCEL_BUTTON_TEXT));
	_cancelButton->setTop(_popUpMessageLabel->getTop() + ONE_CHAR_BUTTON_HEIGHT);
	_cancelButton->setLeft(_confirmButton->getLeft() + _confirmButton->getWidth() + NUMERIC_BOX_LABEL_SPACE_MARGIN);
	_cancelButton->setColor(Color::Black, Color::Red);
}

void
MyMessageBox::closePopUp()
{
	char* fn = __FUNCTION__;
	
	//remove all children except pop up window open button
	_children.erase(_children.begin() + 1, _children.end());
	//restore initial width, height and position
	_top += _height;
	_left += MESSAGE_BOX_LEFT_OFFSET;
	initSize();

	debug(PG_DBG_INFO, "%s: ended. %s: bool", fn, _isConfirmed ? "true" : "false");
	debug(PG_DBG_INFO, "%s: ended. %d: _top	%d: _left", fn, _top, _left);
}
