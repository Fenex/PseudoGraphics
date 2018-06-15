#include "PgList.h"


PgList::PgList() : Control(), multiple_choices(TRUE), select_sym(SYM_CHOICE_CHECKLIST), focused_item_idx(-1)
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
	selected_items.push_back(false);
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

void
PgList::setFocusedItem(const int item_idx)
{
	flipColorsAt(focused_item_idx);
	focused_item_idx = item_idx;
	flipColorsAt(focused_item_idx);
}

bool
PgList::mousePressed(int x, int y, bool isLeft, Graphics& g)
{

	if (!isLeft) {
		return false;
	}

	int item_idx = clickedChildIndex(x, y);
	if (item_idx != -1)
	{
		if(focused_item_idx != item_idx)
			setFocusedItem(item_idx);
		setSelectedItem(item_idx, select_sym);
	}

	return true;
}

void
PgList::keyDown(int keyCode, char character, Graphics& g)
{
	debug(PG_DBG_INFO, "%s: focused_item_idx=%d.", __FUNCTION__, focused_item_idx);
	switch (keyCode)
	{
	case VK_TAB:

		break;
	case VK_NUMPAD8:
	case VK_UP:
		if (focused_item_idx - 1 >= 0)
			setFocusedItem(focused_item_idx-1);
		return;
	case VK_NUMPAD2:
	case VK_DOWN:
		if (focused_item_idx + 1 < _children.size() )
			setFocusedItem(focused_item_idx+1);
		return;

	case VK_RETURN:
	case VK_SPACE:
		setSelectedItem(focused_item_idx, select_sym);
		return;

	default:
		break;
	}
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
		if (multiple_choices == FALSE)
		{
			clearSelection();
		}
		
		string selected = getChildAt(pos)->getValue();
		if (selected[SYM_MARKER_POS] == symbol) {
			selected[SYM_MARKER_POS] = ' ';
			selected_items.at(pos) = false;
		}
		else {
			selected[SYM_MARKER_POS] = symbol;
			selected_items.at(pos) = true;
		}
		getChildAt(pos)->setValue(selected);
	}
}

int
PgList::clickedChildIndex(const short x, const short y)
{
	int child_idx;
	if (isInside(x, y, 
		getLeft() + BORDER_OFFSET, 
		getTop() + BORDER_OFFSET,
		getWidth() - (BORDER_OFFSET * 2), 
		getTop() - (BORDER_OFFSET * 2) - 2 ))
	{
		child_idx = y - getTop() - (BORDER_OFFSET*2);
		if (child_idx < 0 || child_idx > _children.size() - 1)
		{
			child_idx = -1;
		}
	}

	return child_idx;
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