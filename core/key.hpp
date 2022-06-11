#ifndef CORE_KEY_HPP
#define CORE_KEY_HPP

#include <Windows.h>

class CKeyInput {
public:
	unsigned int nTimePressed; // Time (unix timestamp) when nKey was pressed
	unsigned int nTimeReleased; // Time (unix timestamp) when nKey was released
	bool bHeld;

	char cKey; // Display key
	int nKeyCode; // Virtual keycode

	CKeyInput(char cKey) {
		this->cKey = cKey;
		this->nKeyCode = VkKeyScanExA(cKey, GetKeyboardLayout(NULL)); // get the virtual code for our char

		bHeld = false;
		nTimePressed = 0;
		nTimeReleased = 0;
	}

	CKeyInput() {
		// this is called by resize for whatever reason
	}
};

#endif