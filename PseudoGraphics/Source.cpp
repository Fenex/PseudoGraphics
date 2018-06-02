
#include "Graphics.h"
#include "ControlFactory.h"
#include "EventEngine.h"

int main(int argc, char** argv)
{
	//create our controls factory:
	ControlsFactory& factory = ControlsFactory::getInstance();

	//create some controls with out 'enum ControlProduct' helper:
	Control& label = factory.create(LABEL);

	Panel p;
	p.setColor(Color::Purple, Color::Orange);
	p.setLeft(10);
	p.setTop(10);
	p.setWidth(50);
	p.setHeight(20);
	p.setFrameType(DOUBLE_SOLID);

	Button b("KING JAMES");
	b.setLeft(1);
	b.setTop(1);
	b.setColor(Color::Blue, Color::Green);
	p.add(&b);

	Label l("IM A LABEL");
	l.setColor(Color::Cyan, Color::Red);
	l.setLeft(10);
	l.setTop(10);
	p.add(&l);

	Label l2("IM RICK JAMES");
	l2.setColor(Color::Black, Color::Orange);
	l2.setLeft(12);
	l2.setTop(15);
	p.add(&l2);

	Control& panel = p;
	EventEngine e;
	e.run(p);


}