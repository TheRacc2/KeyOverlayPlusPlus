#ifndef CORE_INPUT_HPP
#define CORE_INPUT_HPP

#include "../key.hpp"
#include <vector>
#include <thread>

namespace input {
	inline HHOOK pHook;
	inline std::vector<CKey> vecMonitoredKeys;

	void configureKeys();

	void registerHook();
	void removeHook();

	LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
}

#endif