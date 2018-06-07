#pragma once
#include "Control.h"
#include "Button.h"
class MyMessageBox :
	public Control
{
private:
	bool _isConfirmed;	//indicates whether user confirms pop-up box or not. default is false
	Button *_confirmButton, *_cancelButton;
	Button *_openPopUpButton;
	Label *_popUpMessageLabel;
	string _openPopUpButtonText, _popUpMessage;

	void initButtons();
public:
	MyMessageBox(string popUpButtonText = DEFAULT_POP_UP_BUTTON_TEXT, string popUpMessage = DEFAULT_POP_UP_MESSAGE);
	~MyMessageBox();
	bool myPureFunction() { return false; }
	void draw(Graphics& g);
	bool mousePressed(int x, int y, bool isLeft, Graphics& g);

	bool getConfirmationStatus() { return _isConfirmed; }
	void openPopUp();
	void closePopUp();
	void setButtontext(string);
	void setPopUpMessage();
};

