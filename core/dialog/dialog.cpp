#include "dialog.hpp"
#include "../input/input.hpp"
#include "../assert.hpp"

#include <iostream>

namespace dialog {
	void clearConsole() { // https://stackoverflow.com/questions/6486289/how-can-i-clear-console the proper way
		COORD topLeft = { 0, 0 };

		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		ASSERT(hConsole);

		CONSOLE_SCREEN_BUFFER_INFO screen;
		DWORD dwWritten;

		ASSERT(GetConsoleScreenBufferInfo(hConsole, &screen));
		ASSERT(FillConsoleOutputCharacterA(hConsole, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &dwWritten));
		ASSERT(FillConsoleOutputAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE, screen.dwSize.X * screen.dwSize.Y, topLeft, &dwWritten));
		ASSERT(SetConsoleCursorPosition(hConsole, topLeft));
	}

	void configureKeys() {
		std::cout << "Please enter the key count: ";

		std::string strSize;
		std::getline(std::cin, strSize);
		int nSize = std::stoi(strSize);

		ASSERT(nSize);

		input::vecMonitoredKeys.resize(nSize);
		input::vecMonitoredKeys.clear();

		do {
			// get the virtual key code, add it to the monitored list
			clearConsole();

			std::cout << "Please enter key " << input::vecMonitoredKeys.size() + 1 << ": ";

			std::string strInput;
			std::getline(std::cin, strInput);
			input::vecMonitoredKeys.emplace_back(strInput.at(0));

		} while (input::vecMonitoredKeys.size() != nSize);
	}
}