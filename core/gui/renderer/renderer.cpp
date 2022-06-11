#include "renderer.hpp"

#include "../../../lib/imgui/imgui.h"

namespace renderer {
	void drawRect(int x, int y, int w, int h, int color) { // color in ARGB format, 255 max
		ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), color);
	}
}