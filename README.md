# Pseudo Graphics Library

**Head Lecturer & Tutor** </br>
[Dr. Amit Resh](https://scholar.google.com/citations?user=5lTmLKsAAAAJ&hl=en)</br>
[Asaf Algawi](https://github.com/auval)

**Contributers** </br>
[Shay Rubach](https://github.com/ShayRubach)</br>
[Idan Lazimi](https://github.com/idanlazimi)</br>
[Alon Golan](https://github.com/alongolan1991)</br>


## Description

Pseudo Graphics is a static library API for developing User Interface on windows terminal envirnment. This API consists of creating all needed components and access their content at any time via code.<br>The API is open source !(c) and can be modified to meet any devs need.

## Developing Environment

* Windows 7 **or higher** (Unix a-like users can use [Wine](https://www.winehq.org/))
* C++ **11** and above
* Visual Studio (we used [2017 Community addition](https://www.visualstudio.com/vs/whatsnew/))
	* note: if you use VS, you'll need to define the [following value on project preprocessor definitions](https://stackoverflow.com/a/22450838)

## UI Components Demo

#### Label  <br> ![label](https://user-images.githubusercontent.com/21342315/41190512-427c7e3c-6be0-11e8-9704-8c76768ea64e.png)<br>
#### Button<br>![btn](https://user-images.githubusercontent.com/21342315/41190528-89831ad4-6be0-11e8-9585-12552145c034.png) ![btnclicked](https://user-images.githubusercontent.com/21342315/41190534-d4b6aa34-6be0-11e8-8301-a6f41f9f5d2d.png)<br>
#### TextBox<br> ![tb](https://user-images.githubusercontent.com/21342315/41190544-0addcd4a-6be1-11e8-9d7d-99e9b02c2c50.png)<br>
#### NumericBox<br>![low](https://user-images.githubusercontent.com/21342315/41190550-4e3363c0-6be1-11e8-8ec3-8418c2b2b52e.png)![mid](https://user-images.githubusercontent.com/21342315/41190549-411204da-6be1-11e8-851b-e87c302c0932.png)![high](https://user-images.githubusercontent.com/21342315/41190554-5668e31c-6be1-11e8-8696-080efbbeb73a.png)<br>
#### MessageBox<br>![mb](https://user-images.githubusercontent.com/21342315/41190587-2b0ce3b6-6be2-11e8-9bbf-4a8137c436ab.png)<br>
#### Panel<br>![panel](https://user-images.githubusercontent.com/21342315/41190630-0956cef2-6be3-11e8-9abf-131bf7dce667.png)

## Basic Synthax

Every component can be created with no values passed to constructor. These can be modified and set later - avoiding this will be resulted with **undefined behavior**.<br>

Here are some good practices for instantiating the components:
![table](https://user-images.githubusercontent.com/21342315/41191692-acac5d1e-6bf3-11e8-89f9-cb17dc1b3db7.png)


### Basic Usage Demo

```cpp
#include "Graphics.h"
#include "ControlFactory.h"
#include "EventEngine.h"

int main(int argc, char** argv)
{
	Panel p;
	Control& panel = p;
	p.setColor(Color::Purple, Color::Black);
	p.setLeft(5);
	p.setTop(5);
	p.setWidth(50);
	p.setHeight(40);
	p.setFrameType(DOUBLE_SOLID);

	Button b("Exit");
	b.setLeft(42);
	b.setTop(1);
	b.setColor(Color::Blue, Color::Green);
	p.add(&b);

	TextBox tb(1, 2, 12, 5);
	tb.setColor(Color::Black, Color::White);
	p.add(&tb);

	Label l1("TextBox Title");
	l1.setColor(Color::Cyan, Color::Red);
	l1.setLeft(0);
	l1.setTop(0);
	p.add(&l1);

	Label l2("I'm a label. Below me there's a NumericBox!");
	l2.setColor(Color::Black, Color::Orange);
	l2.setLeft(3);
	l2.setTop(17);
	p.add(&l2);

	NumericBox nb;
	nb.setLeft(20);
	nb.setTop(20);
	p.add(&nb);

	string s("Press me to pop a msg");
	MyMessageBox msg(s, s);
	msg.setLeft(12);
	msg.setTop(30);
	p.add(&msg);

	EventEngine e;
	e.run(panel);

}
```

Will look like this:<br>
![main_demo](https://user-images.githubusercontent.com/21342315/41191625-b40cc284-6bf2-11e8-82d5-1a0363e9af5a.png)