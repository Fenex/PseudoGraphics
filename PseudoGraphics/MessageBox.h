#pragma once
#include "Control.h"
#include "Button.h"
class MyMessageBox :
	public Control
{
private:
	bool _is_confirmed;	//indicates whether user confirms pop-up box or not. default is false
	bool _is_pop_up_open;
	Button *_confirm_button, *_cancel_button;
	Button *_open_pop_up_button;
	Label *_pop_up_message_label;
	string _open_pop_up_button_text, _pop_up_message;

	void initButtons();
	void initSize();
public:
	MyMessageBox(short top, short left, string popUpButtonText = DEFAULT_POP_UP_BUTTON_TEXT, string popUpMessage = DEFAULT_POP_UP_MESSAGE);
	~MyMessageBox();
	bool myPureFunction() { return false; }
	void draw(Graphics& g);
	bool mousePressed(int x, int y, bool isLeft);

	bool getConfirmationStatus() { return _is_confirmed; }
	void openPopUp();
	void closePopUp();
	void setButtontext(string);
	void setPopUpMessage();
};

