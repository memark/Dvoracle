#ifndef _MBHIDHACK_H_
#define _MBHIDHACK_H_

/*
 * $Id: MBHIDHack.h 151 2006-05-03 23:20:47Z mbaltaks $
 *
 * MBHIDHack.h
 * DoubleCommand
 *
 * Created by Michael Baltaks on Tuesday April 30 2002.
 *
 * Last modified 2003-02-06.
 * Copyright (c) 2002 Michael Baltaks. All rights reserved.
 * Thanks to Shane Celis <shane@terraspring.com> for some
 * constants.
 */


// define MB_DEBUG to enable output of keycodes
//#define MB_DEBUG
//#define MB_TESTING

// these should be defined for a 10.2 build, but
// not for 10.3 or later
//#define IOHIDSystem_AVAILABLE
//#define JAGUAR_FLAGS

// Macro which helps clean up and optimise the flag changing code
#define REMOVE(x, y)	( (x) &= ~((x) & (y)) )

// these flags are defined in IOLLEvent.h

#ifdef JAGUAR_FLAGS
	#define COMMAND_FLAG 0x100000
	#define COMMAND_FLAG_R 0x100000
#else
	#define COMMAND_FLAG   0x100008
	#define COMMAND_FLAG_R 0x100010
#endif
#ifdef JAGUAR_FLAGS
	#define CONTROL_FLAG 0x40000
	#define CONTROL_FLAG_R 0x40000
#else
	#define CONTROL_FLAG   0x40001
	#define CONTROL_FLAG_R 0x42000
#endif
#ifdef JAGUAR_FLAGS
	#define SHIFT_FLAG 0x20000
	#define SHIFT_FLAG_R 0x20000
#else
	#define SHIFT_FLAG   0x20002
	#define SHIFT_FLAG_R 0x20004
    #define SHIFT_DIFF_LEFT 0x00002
    #define SHIFT_DIFF_RIGHT 0x00004
#endif
#define CAPSLOCK_FLAG 0x10000
#ifdef JAGUAR_FLAGS
	#define OPTION_FLAG 0x80000
	#define OPTION_FLAG_R 0x80000
#else
	#define OPTION_FLAG   0x80020
	#define OPTION_FLAG_R 0x80040
#endif
#define FN_FLAG 0x800000

#define TAB_KEY 48
#define SPACE_KEY 49
#define SHIFT_KEY 56
#define SHIFT_KEY_R 60
#define CONTROL_KEY 59
#define CONTROL_KEY_R 62
#define CAPSLOCK_KEY 57
// special caps key for TiBook (and probably other models)
#define SPECIAL_CAPSLOCK_KEY 127
#define ENTER_KEY 52
#define POWERBOOKG4_2005_ENTER_KEY 76
#define COMMAND_KEY 55
#define COMMAND_KEY_R 54
#define OPTION_KEY 58
#define OPTION_KEY_R 61
#define FN_KEY 63
#define TILDE_KEY 50
#define DELETE_KEY 51
#define FORWARD_DELETE_KEY 117
#define INSERT_KEY 114
#define NUMPAD_DOT 65
#define HOME_KEY 115
#define END_KEY 119
#define LEFT_ARROW_KEY 123
#define RIGHT_ARROW_KEY 124
#define BACKSLASH_KEY 42
#define CLEAR_KEY 71
#define F1		122
#define F2		120
#define F3		99
#define F4		118
#define F5		96
#define F6		97
#define F7		98
#define F8		100
#define F9		101
#define F10		109
#define F11		103
#define F12		111
#define APP_KEY	110
#define BRIGHTNESS_DOWN		10
#define BRIGHTNESS_UP		9
#define VOLUME_MUTE		8
#define VOLUME_DOWN		7
#define VOLUME_UP		6
#define SPECIAL_KEY		127
#define BRIGHTNESS_DOWN_FLAVOUR		3
#define BRIGHTNESS_UP_FLAVOUR		2
#define VOLUME_MUTE_FLAVOUR		7
#define VOLUME_DOWN_FLAVOUR		1
#define VOLUME_UP_FLAVOUR		0
#define NUMLOCK_FLAVOUR		10
#define F7a_FLAVOUR		15
#define F8a_FLAVOUR		23
#define F9a_FLAVOUR		22
#define F10a_FLAVOUR		21
#define EJECT_FLAVOUR		14
#define F7a		12
#define F8a		13
#define F9a		14
#define F10a	15
#define F11a	103
#define EJECT	11

#define NUMPAD1_KEY 83
#define NUMPAD6_KEY 88

#define KEY_DOWN 10
#define KEY_UP 11
#define KEY_MODIFY 12
#define KEY_CANCEL 0

enum
{
    kKeyDown = 10,
    kKeyUp = 11,
    kKeyModify = 12
};

#define POWERBOOKG3_KEYBOARD 195
#define TIBOOK_KEYBOARD 196
#define IBOOK_KEYBOARD 202
#define APPLE_PRO_2003_KEYBOARD 34
#define POWERBOOKG4_2005_KEYBOARD 37

#define ENTER_TO_COMMAND						0x00000001
#define ENTER_TO_CONTROL						0x00000002
#define ENTER_TO_OPTION							0x00000004
#define ENTER_TO_FN								0x00000008
#define COMMAND_TO_OPTION						0x00000010
#define COMMAND_TO_CONTROL						0x00000020
#define OPTION_TO_COMMAND                       0x00000040
#define OPTION_TO_FN							0x00000080

#define CONTROL_TO_COMMAND						0x00000100
#define SWAP_CONTROL_AND_OPTION					0x00000200
#define CONTROL_TO_FN							0x00000400
#define CAPSLOCK_TO_CONTROL						0x00000800
#define FN_TO_CONTROL							0x00001000
#define REVERSE_NUMPAD_DOT_AND_SHIFT_NUMPAD_DOT	0x00002000
#define SHIFT_DELETE_TO_FORWARD_DELETE			0x00004000
#define DISABLE_COMMAND_AND_OPTION				0x00008000

#define PC_STYLE_HOME_AND_END					0x00010000
#define BACKSLASH_TO_FORWARD_DELETE				0x00020000
#define SWAP_FUNCTION_KEYS						0x00040000
#define CAPSLOCK_DISABLED						0x00080000
#define ENTER_TO_FORWARD_DELETE					0x00100000
#define CONTROL_TO_DELETE						0x00200000
#define DELETE_TO_CONTROL						0x00400000
#define MB_DEBUG_OUTPUT							0x00800000
#define SWAP_TILDE_AND_COMMAND					0x01000000
#define TYPEMATRIX_SUPPORT                      0x02000000
#define SHIFT_LIMIT_MODE                        0x04000000
//#define                                       0x08000000
//#define                                       0x10000000
//#define                                       0x20000000
//#define                                       0x40000000
//#define                                       0x80000000
#define NEED_NEW_INT_VAR                       0x100000000

#endif // _MBHIDHACK_H_
