#include <Windows.h>
#include <iostream>
#include <vector>

#include "key.hpp"
#include "gui/gui.hpp"
#include "input/input.hpp"

void clear() {
	COORD topLeft = { 0, 0 };
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen;
	DWORD written;

	GetConsoleScreenBufferInfo(console, &screen);
	FillConsoleOutputCharacterA(
		console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
	);
	FillConsoleOutputAttribute(
		console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
		screen.dwSize.X * screen.dwSize.Y, topLeft, &written
	);
	SetConsoleCursorPosition(console, topLeft);
}


int main() {
	SetConsoleTitleA("KeyOverlay++ Backend");

	std::cout << "Configurations will be added soon." << std::endl;
	input::configureKeys();

	clear();
	
	input::registerHook();
	gui::init();

	bool bClose = false;
	do {
		bClose = gui::loop();
	} while (!bClose); // wait until the window is closed

	gui::end();
	input::removeHook();
}