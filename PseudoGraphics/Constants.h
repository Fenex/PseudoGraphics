//This header file is used to hold every shared constants between the project components
#pragma once
#ifndef CONSTANTS_H
#define CONSTANTS_H

//special char set:
//single line
#define BORDER_OFFSET (1)
#define SINGLE_TOP_LEFT_CORNER '\xDA'
#define SINGLE_TOP_RIGHT_CORNER '\xBF'
#define SINGLE_BTM_LEFT_CORNER '\xC0'
#define SINGLE_BTM_RIGHT_CORNER '\xD9'
#define SINGLE_LINE_VERTICAL '\xB3'
#define SINGLE_LINE_HORIZONTAL '\xC4'
//double line
#define DOUBLE_TOP_LEFT_CORNER '\xC9'
#define DOUBLE_TOP_RIGHT_CORNER '\xBB'
#define DOUBLE_BTM_LEFT_CORNER '\xC8'
#define DOUBLE_BTM_RIGHT_CORNER '\xBC'
#define DOUBLE_LINE_VERTICAL '\xBA'
#define DOUBLE_LINE_HORIZONTAL '\xCD'

#define BACKSPACE '\x08'
#define SPACE '\x20'
#define CHAR_RESET '\x0'

//list symbols:
#define SYM_BULLET "( )"
#define SYM_MARKER "<---"
#define SYM_SPACE ' '
#define SYM_CLEAR  "    "
#define SYM_CHOICE '*'
#define SYM_CHOICE_OFFSET (3)
#define PROMPT_OFFSET (36)

//default gui values
#define POS_DEF_X (5)
#define POS_DEF_Y (5)
#define DIM_DEF_W (5)
#define DIM_DEF_H (5)
#define MIN_DIM_X (3)
#define MIN_DIM_Y (3)
#define DEFAULT_CURSOR_SIZE (50)
#define DEFAULT_LABEL_STR "RICK AND MORTY"
#define BORDER_OFFSET (2)


//default component colors:
#define DEF_PANEL_COLOR (5)
#define DEF_LABEL_COLOR (90|10|30)
#define DEF_BTN_COLOR		(100|20|200)


//debug
#define PG_INFO				"INFO";
#define PG_ERR				"ERROR";
#define PG_STANDARD		"DBG";
#define DBG_FILE_NAME "debug.txt"



#endif // !CONSTANTS_H


