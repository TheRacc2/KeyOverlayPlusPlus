#ifndef CORE_KEY_HPP
#define CORE_KEY_HPP

#include <Windows.h>
#include <deque>

class CKeyInput {
public:
	double dStart, dEnd;
};

class CKey {
public:
	bool bWasHeld;
	bool bHeld;

	unsigned char cKey; // Display key
	int nKeyCode; // Virtual keycode

	std::deque<CKeyInput> deqKeyHistory { };

	CKey(const unsigned char cKey) {
		this->cKey = cKey;

		nKeyCode = VkKeyScanExA(cKey, GetKeyboardLayout(NULL)); // get the virtual code for our char
		if (nKeyCode == -1)
			throw std::exception("Failed to translate cKey into a Virtual-Key!");

		bWasHeld = false;
		bHeld = false;
	}

	CKey() {
		// this is called by resize for whatever reason
	}
};

#endif