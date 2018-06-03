#pragma once
#include "MessageBox.h"
#include "Button.h"


MyMessageBox::MyMessageBox(string popUpButtonText, string popUpMessage)
{
	char* fn = __FUNCTION__;

	_popUpMessage = popUpMessage;
	_openPopUpButtonText = popUpButtonText;
	_height = MESSAGE_BOX_DEFAULT_HEIGHT;
	_width = 1.5 * _popUpMessage.size();
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
	return false;
}

void
MyMessageBox::openPopUp()
{
	add(_popUpMessageLabel = new Label(_popUpMessage));
	_popUpMessageLabel->setTop(_top);
	_popUpMessageLabel->setLeft(_left + NUMERIC_BOX_LABEL_SPACE_MARGIN);
	_popUpMessageLabel->setColor(Color::Black, Color::Red);
	_popUpMessageLabel->setHeight(10);
}
