#pragma once

enum class InputMouseButton {
	UNKNOWN,
	MOUSE_LEFT,
	MOUSE_RIGHT
};

enum class InputKey {
	UNKNOWN,
	KEY_W,
	KEY_A,
	KEY_S,
	KEY_D,
	KEY_F,
	KEY_E,
	KEY_0,
	KEY_1,
	KEY_2,
	KEY_3,
	KEY_4,
	KEY_5,
	KEY_6,
	KEY_7,
	KEY_8,
	KEY_9,
	KEY_LEFT_CTRL,
	KEY_SPACE,
	KEY_LEFT_SHIFT,
	KEY_ESC
};

enum class InputAction {
	UNKNOWN,
	PRESS,
	RELEASE
	//REPEAT
};