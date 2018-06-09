
#include "Graphics.h"
#include "ControlFactory.h"
#include "EventEngine.h"

int main(int argc, char** argv)
{
	//create our controls factory:
	ControlsFactory& factory = ControlsFactory::getInstance();

	//create some controls with out 'enum ControlProduct' helper:
	Control& f_label = factory.create(LABEL);
	Control& f_btn = factory.create(BUTTON);
	Control& f_tb = factory.create(TEXT_BOX);

	Panel p,p2;
	Control& panel = p;
	p.setColor(Color::Purple, Color::Black);
	p.setLeft(5);
	p.setTop(5);
	p.setWidth(50);
	p.setHeight(40);
	p.setFrameType(DOUBLE_SOLID);

	//Button b("Click Me");
	//b.setLeft(20);
	//b.setTop(5);
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
	//string s("Do you really want to exit?");
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
	e.run(panel);


}