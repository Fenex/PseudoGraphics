#pragma once
#include "Control.h"
#include "Button.h"
class MyMessageBox :
	public Control
{
private:
	bool _isConfirmed;	//indicates whether user confirms pop-up box or not. default is false
	Button *_confirm_button, *_cancel_button;
	Button *_open_pop_up_button;
	Label *_pop_up_message_label;
	string _open_pop_up_button_text, _popUpMessage;

	void initButtons();
	void initSize();
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

