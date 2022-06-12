#include "input.hpp"

#include <Windows.h>
#include <thread>
#include <iostream>

namespace input {
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