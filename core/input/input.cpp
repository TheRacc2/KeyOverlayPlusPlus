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
			vecMonitoredKeys.emplace_back(cInput);

		} while (vecMonitoredKeys.size() != nSize);
	}

	LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
		if (nCode == HC_ACTION) {
			PKBDLLHOOKSTRUCT pEvent = (PKBDLLHOOKSTRUCT) lParam;

			CKey* monitoredKey = nullptr; // check if this key is monitored
			for (CKey& key : vecMonitoredKeys) { // TODO: use std::find_if instead
				if (key.nKeyCode == pEvent->vkCode)
					monitoredKey = &key;
			}

			if (monitoredKey) { // this will be nullptr if the key is not monitored
				switch (wParam) {
					case WM_KEYDOWN:
						monitoredKey->bHeld = true;
					break;

					case WM_KEYUP:
						monitoredKey->bHeld = false;
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