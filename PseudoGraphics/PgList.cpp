#include "PgList.h"


PgList::PgList() : Control(), _multiple_choices(TRUE)
{
	setFocusable(TRUE);
	setClickable(TRUE);
	setFrameType(SINGLE_SOLID);
	_focusable = true;
	_clickable = true;
}

PgList::~PgList() {}

Button*
PgList::initButton(string value)
{
	Button* btn = new Button(value);
	btn->setFocusable(true);
	btn->setClickable(false);
	btn->setFrameType(NONE);
	btn->setWidth(getWidth() - (BORDER_OFFSET * 2));
	btn->setHeight(1);
	btn->setColor(_background, _foreground);
	btn->setTop(getTop() + BORDER_OFFSET + getChildren().size());
	btn->setLeft(getLeft() + BORDER_OFFSET * 2);
	return btn;
}

bool
PgList::addItem(string item)
{
	// if we're at max items in our list, do nothing:
	if (getHeight() - (BORDER_OFFSET * 2) - 2 == _children.size())
	{
		return false;
	}

	string fixed_item;
	fixed_item.append(SYM_BULLET).append(SYM_SPACE).append(item);
	_children.push_back(initButton(fixed_item));
	return true;
}

void
PgList::draw(Graphics& g)
{
	Control::draw(g);

	//get the original terminal color back to black:
	g.setBackground(Color::Black);
}

bool
PgList::removeSelectedItem()
{
	return true;
}

bool
PgList::mousePressed(int x, int y, bool isLeft, Graphics& g)
{

	if (!isLeft) {
		return false;
	}

	int item_idx = clickedChildIndex(x, y);

	return true;
}

void
PgList::keyDown(int keyCode, char character, Graphics& g)
{

}

void
PgList::clearSelection()
{
	for each (Button* child in _children)
	{
		string selected = child->getValue();
		selected[SYM_MARKER_POS] = ' ';
		child->setValue(selected);
	}
	return;
}

int
PgList::getSelectedItemPos()
{
	return 1;
}

string
PgList::getSelectedItemValue()
{
	return "default value";

}

bool
PgList::isValidIndex(int idx)
{
	return (idx < 0 || idx > _children.size() - 1) ? false : true;
}

void
PgList::setSelectedItem(const int pos, char symbol)
{

	if (isValidIndex(pos))
	{
		if (_multiple_choices == FALSE)
		{
			clearSelection();
		}

		string selected = getChildAt(pos)->getValue();
		selected[SYM_MARKER_POS] = symbol;

		getChildAt(pos)->setValue(selected);
	}
}

int
PgList::clickedChildIndex(const short x, const short y)
{
	if (isInside(x, y, getLeft() + BORDER_OFFSET, getTop() + BORDER_OFFSET, getWidth() - (BORDER_OFFSET * 2), getTop() - (BORDER_OFFSET * 2)))
	{
		//do stuff..	
	}

	return -1;
}

bool
PgList::isMouseOnSelectedItem(const short x, const short y)
{
	return true;
}

Button*
PgList::getChildAt(int pos)
{
	if (isValidIndex(pos) == true)
	{
		return static_cast<Button*>(_children.at(pos));
	}
	return NULL;
}

void 
PgList::flipColorsAt(int item_pos)
{
	if (isValidIndex(item_pos) == true)
	{
		_children.at(item_pos)->flipColor();
	}
}