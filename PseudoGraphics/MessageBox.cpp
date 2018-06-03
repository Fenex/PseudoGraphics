#pragma once
#include "MessageBox.h"
#include "Button.h"


MyMessageBox::MyMessageBox(string popUpButtonText, string popUpMessage)
{
	char* fn = __FUNCTION__;

	_popUpMessage = popUpMessage;
	_openPopUpButtonText = popUpButtonText;
	_height = MESSAGE_BOX_DEFAULT_HEIGHT;
	_width = NUMERIC_BOX_LABEL_SPACE_MARGIN + _popUpMessage.size();
	_isConfirmed = false;
	debug(PG_DBG_INFO, "%s: called. %s: popUpButtonString", fn, _openPopUpButtonText.c_str());
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
	_openPopUpButton->setTop(_top + _height - ONE_CHAR_BUTTON_HEIGHT);
	_openPopUpButton->setLeft(_left + 0.5*_popUpMessage.size());
	_openPopUpButton->setColor(Color::Black, Color::Red);
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
	//display label and buttons
	add(_popUpMessageLabel = new Label(_popUpMessage));
	_popUpMessageLabel->setTop(_top);
	_popUpMessageLabel->setLeft(_left + NUMERIC_BOX_LABEL_SPACE_MARGIN);
	_popUpMessageLabel->setColor(Color::Black, Color::Red);
	_popUpMessageLabel->setFrameType(SINGLE_SOLID);
	_popUpMessageLabel->setWidth(_width);
	_popUpMessageLabel->setHeight(_height - ONE_CHAR_BUTTON_HEIGHT);
	
	add(_confirmButton = new Button("Confirm"));
	_confirmButton->setTop(_top + ONE_CHAR_BUTTON_HEIGHT);
	_confirmButton->setLeft(_left + 0.2*_width + NUMERIC_BOX_LABEL_SPACE_MARGIN);
	_confirmButton->setColor(Color::Black, Color::Red);

	add(_cancelButton = new Button("Cancel"));
	_cancelButton->setTop(_top + ONE_CHAR_BUTTON_HEIGHT);
	_cancelButton->setLeft(_confirmButton->getLeft() + _confirmButton->getWidth() + NUMERIC_BOX_LABEL_SPACE_MARGIN);
	_cancelButton->setColor(Color::Black, Color::Red);
}

void
MyMessageBox::closePopUp()
{
	char* fn = __FUNCTION__;
	
	//remove all children except pop up window open button
	_children.erase(_children.begin() + 1, _children.end());
	debug(PG_DBG_INFO, "%s: ended. %s: bool", fn, _isConfirmed ? "true" : "false");
}
