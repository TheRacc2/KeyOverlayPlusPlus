#include <Windows.h>
#include <iostream>
#include <vector>

#include "key.hpp"
#include "gui/gui.hpp"
#include "input/input.hpp"

int main() {
	SetConsoleTitleA("KeyOverlay++ Backend");

	std::cout << "Configurations will be added soon." << std::endl;
	input::configureKeys();

	system("cls");
	
	input::registerHook();
	gui::init();

	bool bClose = false;
	do {
		bClose = gui::loop();
	} while (!bClose); // wait until the window is closed

	gui::end();
	input::removeHook();
}