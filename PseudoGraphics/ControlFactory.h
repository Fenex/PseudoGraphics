#pragma once
#ifndef CONTROLS_FACTORY_H
#define CONTROLS_FACTORY_H


#include <iostream>
#include "Button.h"
#include "Panel.h"
#include "TextBox.h"

typedef enum {
	LABEL,
	BUTTON,
	CHECK_LIST,
	MESSAGE_BOX,
	COMBO_BOX,
	RADIO_BOX,
	TEXT_BOX,
	NUMERIC_BOX,
	PANEL
} ControlProduct;

//Singleton Factory
class ControlsFactory final
{
private:
	//prohibiting copying and instanciating with c++11 delete modifier
	ControlsFactory() {}
	ControlsFactory(const ControlsFactory&) = delete;
	ControlsFactory& operator=(const ControlsFactory&) = delete;

public:
	static ControlsFactory& getInstance();
	Control& create(ControlProduct product);

};

#endif // !CONTROLS_FACTORY_H
