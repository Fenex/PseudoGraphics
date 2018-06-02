#include "Panel.h"
#include "Graphics.h"



Panel::Panel() : Control()
{
}


Panel::~Panel()
{
	
}

bool
Panel::myPureFunction() 
{ 
	return true; 
}

bool
Panel::mousePressed(int x, int y, bool isLeft) 
{
	vector<Control*> children = this->getChildren();
	for each(Control* cp in children) {
		if (isInside(x, y, cp->getLeft(), cp->getTop(), cp->getWidth(), cp->getHeight())) {
			cp->mousePressed(x, y, true);
			return true;
		}
	}
	return false;

}
