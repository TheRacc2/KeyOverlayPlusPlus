#include "config.hpp"

#include <fstream>

namespace config {
	void parse() {
		if (std::filesystem::exists("config.json")) {
			std::ifstream stream("config.json");
			stream >> file;
			stream.close();
		}
		else {
			file = {
				{ "keyBox", {
					{ "spacing", 10 },
					{ "size", 50 },
					{ "outlineThickness", 3 }
				}},

				{ "text", {
					{ "forceUppercase", true },
					{ "vertical", false },
					{ "font", R"(C:\Windows\Fonts\Tahoma.ttf)"}
				}},

				{ "colors", {
					{ "outline", 0xFFFFFFFF },
					{ "fill", 0xB4B4B4B9 },
					{ "history", 0xB4B4B4B9 },
					{ "text", 0xFFFFFFFF }
				}},

				{ "history", {
					{ "enabled", true }, 
					{ "scrollSpeed", 400 },
					{ "fadeDistance", 100 },
					{ "fadeOut", true }
				}},
			};

			std::ofstream stream("config.json");
			stream << file.dump(4);
			stream.close();
		}
	}
}