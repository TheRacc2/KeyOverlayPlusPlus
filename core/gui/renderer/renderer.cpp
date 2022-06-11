#include "renderer.hpp"

#include "../../../lib/imgui/imgui.h"

namespace renderer {
	void drawRect(int x, int y, int w, int h, unsigned int color) { // color in ARGB format, 255 max
		ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), color);
	}

	void drawRectOutline(int x, int y, int w, int h, int r, int t, unsigned int color) { // color in ARGB format, 255 max
		ImGui::GetWindowDrawList()->AddRect(ImVec2(x, y), ImVec2(x + w, y + h), color, r, NULL, t);
	}

	void drawGradientVertical(int x, int y, int w, int h, unsigned int bottomColor, unsigned int topColor) {
		ImGui::GetWindowDrawList()->AddRectFilledMultiColor(ImVec2(x, y), ImVec2(x + w, y + h),
			topColor, topColor, bottomColor, bottomColor
		);
	}
}