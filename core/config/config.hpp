#ifndef CORE_CONFIG_HPP
#define CORE_CONFIG_HPP

#include <nlohmann/json.hpp>
#include <fstream>
#include <filesystem>

namespace config {
	namespace gui {
		inline int nKeySpacing = 10;
		inline int nSize = 50;

		inline int nOutlineColor = 0xFFFFFFFF;
		inline int nFillColor = 0xB9B4B4B4;

		inline int nScrollSpeed = 400;
		inline int nFadeDistance = 200;

		inline bool bForceUppercase = true;
		inline bool bIsVertical = false;
		inline bool bFadeOut = false;
	}

	void parse();
}

#endif