#ifndef GUI_RENDERER_HPP
#define GUI_RENDERER_HPP

namespace renderer {
	void drawRect(int x, int y, int w, int h, unsigned int color);
	void drawRectOutline(int x, int y, int w, int h, int r, int t, unsigned int color);
	void drawGradientVertical(int x, int y, int w, int h, unsigned int bottomColor, unsigned int topColor);
}

#endif