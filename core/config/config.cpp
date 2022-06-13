#include "config.hpp"

#include <fstream>
#include <string>

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
					{ "outline", "#FFFFFFFF" },
					{ "fill", "#B4B4B4B9" },
					{ "history", "#B4B4B4B9" },
					{ "text", "#FFFFFFFF" }
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

		for (auto& itr : file["colors"]) { // convert hex to decimal
			std::string hex = itr.get<std::string>();

			if (hex.starts_with("#"))
				hex = hex.substr(1);

			if (hex.starts_with("0x"))
				hex = hex.substr(2);

			if (!(hex.length() > 6)) // does it have alpha?
				hex += "FF";

			for (int i = 0; i < hex.length(); i++)
				hex[i] = toupper(hex[i]);

			unsigned int decimal = std::stoul(hex, nullptr, 16);
			itr = decimal;
		}
	}
}