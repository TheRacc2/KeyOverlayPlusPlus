#include "renderer.hpp"
#include "../gui.hpp"

#include <format>
#include <iostream>

namespace renderer {
	void drawRect(int x, int y, int w, int h, int color) { // color in RGBA format, 255 max
		ImVec4 RGBA = ImGui::ColorConvertU32ToFloat4(color); // this is dumb
		ImU32 ABGR = ImGui::ColorConvertFloat4ToU32(ImVec4(RGBA.w, RGBA.z, RGBA.y, RGBA.x));

		ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), ABGR);
	}

	void drawRectOutline(int x, int y, int w, int h, int r, int t, unsigned int color) { // color in RGBA format, 255 max
		ImGui::GetWindowDrawList()->AddRect(ImVec2(x, y), ImVec2(x + w, y + h), color, r, NULL, t);
	}

	void drawGradientVertical(int x, int y, int w, int h, int bottomColor, int topColor) {
		ImVec4 bottom = ImGui::ColorConvertU32ToFloat4(bottomColor);
		ImVec4 top = ImGui::ColorConvertU32ToFloat4(topColor);

		ImU32 bottomAGBR = ImGui::ColorConvertFloat4ToU32(ImVec4(bottom.w, bottom.z, bottom.y, bottom.x));
		ImU32 topABGR = ImGui::ColorConvertFloat4ToU32(ImVec4(top.w, top.z, top.y, top.x));

		ImGui::GetWindowDrawList()->AddRectFilledMultiColor(ImVec2(x, y), ImVec2(x + w, y + h), topABGR, topABGR, bottomAGBR, bottomAGBR);
	}
}