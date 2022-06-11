#include "input.hpp"

#include <Windows.h>
#include <thread>
#include <iostream>

namespace input {
	void configureKeys() {
		std::cout << "Please enter the key count: ";
		int nSize; std::cin >> nSize;
		vecMonitoredKeys.resize(nSize); vecMonitoredKeys.clear();

		do {
			// get the virtual key code, add it to the monitored list
			system("cls");

			std::cout << "Please enter key " << vecMonitoredKeys.size() + 1 << ": ";

			char cInput;
			std::cin >> cInput;
			vecMonitoredKeys.push_back(CKeyInput(cInput));

		} while (vecMonitoredKeys.size() != vecMonitoredKeys.capacity());
	}

	LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
		if (nCode == HC_ACTION) {
			PKBDLLHOOKSTRUCT pEvent = (PKBDLLHOOKSTRUCT) lParam;

			CKeyInput* monitoredKey = nullptr; // check if this key is monitored
			for (CKeyInput& key : vecMonitoredKeys) {
				if (key.nKeyCode == pEvent->vkCode)
					monitoredKey = &key;
			}

			if (monitoredKey) { // this will be nullptr if the key is not monitored
				switch (wParam) {
					case WM_KEYDOWN: {
						if (monitoredKey->bHeld) // ignore repeat events
							break;

						monitoredKey->bHeld = true;

						CKeyInput add(monitoredKey->cKey);
						add.nTimePressed = pEvent->time;
						vecKeyHistory.push_back(add);
					}
					break;

					case WM_KEYUP: {
						for (CKeyInput& key : vecKeyHistory) {
							if (key.nKeyCode == pEvent->vkCode && key.nTimePressed && !key.nTimeReleased)
								key.nTimeReleased = pEvent->time, monitoredKey->bHeld = false;
						}
					}
					break;
				}
			}
		}
		
		return CallNextHookEx(NULL, nCode, wParam, lParam);
	}

	void registerHook() {
		pHook = SetWindowsHookExW(WH_KEYBOARD_LL, LowLevelKeyboardProc, NULL, NULL);
	}

	void removeHook() {
		UnhookWindowsHookEx(pHook);
	}
}