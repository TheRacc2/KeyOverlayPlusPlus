#ifndef CORE_GUI_HPP
#define CORE_GUI_HPP

#include <gl/glew.h>
#include <gl/GL.h>
#include <GLFW/glfw3.h>
#include <gl/freeglut.h>
#include <thread>
#include <exception>

#include "../../lib/imgui/imgui.h"
#include "../../lib/imgui/backend/imgui_impl_glfw.h"
#include "../../lib/imgui/backend/imgui_impl_opengl3.h"
#include "../key.hpp"

struct TFontStorage {
	ImFont* tahoma;
};

namespace gui {
	inline GLFWwindow* hWindow = nullptr;
	inline TFontStorage fonts;
	inline std::thread thread;

	void init();

	bool loop();

	void drawKeyLane(CKeyInput& key, int nTimes);
	void drawOverlay();

	void end();
}

#endif