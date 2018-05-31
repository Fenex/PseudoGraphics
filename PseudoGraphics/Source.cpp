#include "Graphics.h"
#include "Label.h"
#include "EventEngine.h"

int main(int argc, char** argv)
{

	Label l("Hello World");
	Control& l2 = l;
	EventEngine e;
	e.run(l);

}