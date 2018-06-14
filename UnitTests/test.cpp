#include "pch.h"
#include "../PseudoGraphics/Graphics.h"
#include "../PseudoGraphics/ControlFactory.h"

namespace PseudoGraphicsUnitTestings {

	const short DEF_PANEL_LEFT = 0;
	const short DEF_PANEL_TOP = 0;
	const short DEF_PANEL_W = 50;
	const short DEF_PANEL_H = 50;
	const short INITIAL_LEFT = 1;
	const short INITIAL_LABEL_TOP = 10;

	/*
		This object is a shared object utility to be used in all cases without the need
		to instantiate the type in each and every test again and again
	*/
	struct SharedUtil : testing::Test {

		Graphics g;
		Panel p;

		SharedUtil() {
			g.clearScreen();
			p.setLeft(DEF_PANEL_LEFT);
			p.setTop(DEF_PANEL_TOP);
			p.setWidth(DEF_PANEL_W);
			p.setHeight(DEF_PANEL_H);

			generateChildrenUsingFactory(p);

		}

		void generateChildrenUsingFactory(Panel& p) {
			//using control factory, just for the sake of demonstration:
			ControlsFactory& factory = ControlsFactory::getInstance();
			Control& f_label = factory.create(LABEL);
			Control& f_btn = factory.create(BUTTON);
			Control& f_tb = factory.create(TEXT_BOX);

			f_label.setFrameType(NONE);
			f_label.setLeft(INITIAL_LEFT);
			f_label.setTop(INITIAL_LABEL_TOP);
			f_tb.setLeft(INITIAL_LEFT);
			f_tb.setTop(30);

			static_cast<Label*>(&f_label)->setValue("Not empty!");

			p.add(&f_label);
			p.add(&f_tb);


		}

		~SharedUtil() {}
		virtual void SetUp() {}
		virtual void TearDown(){}

	};

	/*Text Fixture is used here to contain the shared util obj among all test as we mentioned above.
	  Test basic declaration syntax is:
			Object   |    Test name              */

	
	TEST_F(SharedUtil, panel_isnt_empty) {
		ASSERT_LT(0, p.getChildren().size());
	}

	TEST_F(SharedUtil, panel_is_clickable) {
		p.setClickable(true);
		EXPECT_TRUE(p.canBeClicked());
	}

	TEST_F(SharedUtil, panel_is_focusable) {
		p.setClickable(true);
		EXPECT_TRUE(p.canGetFocus());
	}

	TEST_F(SharedUtil, label_not_empty) {
		EXPECT_FALSE(p.getChildren().at(0)->getStringValue().empty());
	}

	TEST_F(SharedUtil, label_no_border) {
		EXPECT_EQ(NONE, p.getChildren().at(0)->getFrameType());
	}

	TEST_F(SharedUtil, fixed_position_related_to_panel) {
		ASSERT_EQ(p.getLeft() + INITIAL_LEFT, p.getChildren().at(0)->getLeft());
		ASSERT_EQ(p.getTop() + INITIAL_LABEL_TOP, p.getChildren().at(0)->getTop());
	}

	TEST_F(SharedUtil, textbox_is_empty) {
		EXPECT_TRUE(static_cast<TextBox*>(p.getChildren().at(1))->getStringValue().empty());
	}

}