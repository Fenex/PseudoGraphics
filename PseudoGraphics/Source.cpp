
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
	p.setLeft(10);
	p.setTop(10);
	p.setWidth(50);
	p.setHeight(30);
	p.setFrameType(DOUBLE_SOLID);

	//Button b("KING JAMES");
	//b.setLeft(1);
	//b.setTop(1);
	//b.setColor(Color::Blue, Color::Green);
	//p.add(&b);

	//
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

	//
	//
	/*NumericBox numBo(10,10);
	panel.add(&numBo);*/

	string txt("this is a message box");
	string btn("Fuck Me");

	MyMessageBox msg(20, 20, btn,txt);
	panel.add(&msg);

	/*vector<string> options_list = { "abcd","abcde","abcdefg","123456789101112" };
	ComboBox combox(10, 10, options_list);
	panel.add(&combox);*/


	EventEngine e;
	e.run(p);


}