#ifndef CORE_CONFIG_HPP
#define CORE_CONFIG_HPP

#include <nlohmann/json.hpp>
#include <fstream>
#include <filesystem>

namespace config {
	inline nlohmann::json file;

	void parse();
}

#endif