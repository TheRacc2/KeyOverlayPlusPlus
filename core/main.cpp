#include <Windows.h>
#include <iostream>
#include <vector>

#include "key.hpp"
#include "gui/gui.hpp"
#include "input/input.hpp"
#include "config/config.hpp"


int main() {
	SetConsoleTitleA("KeyOverlay++ Backend");

	config::parse();
	input::configureKeys();
	
	ShowWindow(GetConsoleWindow(), SW_HIDE);

	input::registerHook();
	gui::init();

	bool bClose = false;
	do {
		bClose = gui::loop();
	} while (!bClose); // wait until the window is closed

	gui::end();
	input::removeHook();
}