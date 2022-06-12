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
				{ "keySpacing", 10 },
				{ "keySize", 50 },

				{ "outlineColor", 0xFFFFFFFF },
				{ "fillColor", 0xB9B4B4B4 },

				{ "scrollSpeed", 400 },
				{ "fadeDistance", 100 },

				{ "forceUppercase", true },
				{ "vertical", false },
				{ "fadeOut", true }
			};

			std::ofstream stream("config.json");
			stream << file.dump(4);
			stream.close();
		}
	}
}