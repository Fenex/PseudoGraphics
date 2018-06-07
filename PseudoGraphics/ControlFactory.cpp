#include "ControlFactory.h"

//this works due to c++11 local statics approach:
ControlsFactory&
ControlsFactory::getInstance() {
	static ControlsFactory instance;
	return instance;
}

Control&
ControlsFactory::create(ControlProduct product) {
	Control* control = NULL;
	switch (product)
	{
	case LABEL:
		control = new Label;
		break;
	case BUTTON:
		control = new Button();
		break;
	case PANEL:
		control = new Panel();
		break;
	case CHECK_LIST:
		//control = new CheckList();
		break;
	case COMBO_BOX:
		//control =  new ComboBox();
		break;
	case MESSAGE_BOX:
		//control = new MessageBox();
		break;
	case RADIO_BOX:
		//control = new RadioBox();
		break;
	case NUMERIC_BOX:
		//control = new NumericBox();
	case TEXT_BOX:
		control = new TextBox();
		break;
	default:
		break;
	}
	return *control;
}
