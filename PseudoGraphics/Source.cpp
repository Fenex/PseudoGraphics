
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


	p2.setColor(Color::Orange, Color::Black);
	p2.setLeft(5);
	p2.setTop(15);
	p2.setWidth(30);
	p2.setHeight(20);
	p2.setFrameType(DOUBLE_SOLID);

	//Button b("Click Me");
	//b.setLeft(20);
	//b.setTop(5);
	//b.setColor(Color::Blue, Color::Green);
	//p.add(&b);

	TextBox tb(1, 1, 12, 5);
	tb.setColor(Color::Black, Color::White);
	p.add(&tb);


	TextBox tb2(10, 10, 12, 5);
	tb2.setColor(Color::Black, Color::White);
	p2.add(&tb2);

	p.add(&p2);

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


	debug(PG_DBG_INFO, "%s: tb = {%d,%d}", __FUNCTION__, tb.getLeft(), tb.getTop());

	//string s("Do you really want to exit?");
	//
	//MyMessageBox msg(s, s);
	//msg.setLeft(20);
	//msg.setTop(20);
	//p.add(&msg);

	//NumericBox numBo;
	//numBo.setLeft(10);
	//numBo.setTop(10);
	//panel.add(&numBo);


	EventEngine e;
	e.run(panel);


}