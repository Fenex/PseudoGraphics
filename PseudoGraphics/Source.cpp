
#include "Graphics.h"
#include "ControlFactory.h"
#include "EventEngine.h"

#define DEBUG_ON		(0)

int main(int argc, char** argv)
{
	//create our controls factory:
	ControlsFactory& factory = ControlsFactory::getInstance();

	//create some controls with out 'enum ControlProduct' helper:
	Control& label = factory.create(LABEL);
	

	Control& btn = Button("IM A BUTTON");
	
	EventEngine e;
	e.run(btn);



	//delete debug file if turned off
	if (!DEBUG_ON) {
		remove(DBG_FILE_NAME);
	}
}