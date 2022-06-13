#include <Windows.h>
#include <iostream>
#include <vector>

#include "key.hpp"
#include "gui/gui.hpp"
#include "input/input.hpp"
#include "config/config.hpp"
#include "dialog/dialog.hpp"


int main() {
	try {
		SetConsoleTitleA("KeyOverlay++ Backend");

		config::parse();
		dialog::configureKeys();

#ifndef _DEBUG // doing this in debug breaks visual studio for some reason
		ShowWindow(GetConsoleWindow(), SW_HIDE);
#endif

		input::registerHook();
		gui::init();

		bool bClose = false;
		do {
			bClose = gui::loop();
		} while (!bClose); // wait until the window is closed

		gui::end();
		input::removeHook();

		return EXIT_SUCCESS;
	}
	catch (const std::exception& ex) {
		MessageBoxA(nullptr, ex.what(), "KeyOverlay++ | Error", MB_OK);
		return EXIT_FAILURE;
	}
}