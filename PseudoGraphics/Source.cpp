
#include "Graphics.h"
#include "ControlFactory.h"
#include "EventEngine.h"

#define DEBUG_ON		(1)

int main(int argc, char** argv)
{
	//create our controls factory:
	ControlsFactory& factory = ControlsFactory::getInstance();

	//create some controls with out 'enum ControlProduct' helper:
	Control& label = factory.create(LABEL);
	EventEngine e;
	e.run(label);

}

