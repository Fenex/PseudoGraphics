
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
	Control& panel = p;
	p.setColor(Color::Purple, Color::Orange);
	p.setLeft(0);
	p.setTop(0);
	p.setWidth(50);
	p.setHeight(80);
	p.setFrameType(DOUBLE_SOLID);


	//Button b("KING JAMES");
	//b.setLeft(1);
	//b.setTop(1);
	//b.setColor(Color::Blue, Color::Green);
	//p.add(&b);


	//Label l("IM A LABEL");
	//l.setColor(Color::Cyan, Color::Red);
	//l.setLeft(10);
	//l.setTop(10);
	//p.add(&l);

	//Label l2("IM RICK JAMES");
	//l2.setColor(Color::Black, Color::Orange);
	//l2.setLeft(12);
	//l2.setTop(15);
	//p.add(&l2);


	//NumericBox numBo;
	//numBo.setLeft(30);
	//numBo.setTop(20);
	//p.add(&numBo);

	//string s("this is a message box");
	//
	//MyMessageBox msg(s, s);
	//msg.setLeft(10);
	//msg.setTop(30);
	//p.add(&msg);

	TextBox tb(1, 1, 12, 5);
	tb.setColor(Color::Black, Color::White);
	p.add(&tb);


	//NumericBox numBo;
	//numBo.setLeft(10);
	//numBo.setTop(10);
	//panel.add(&numBo);


	EventEngine e;
	e.run(p);


}