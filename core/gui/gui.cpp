#include "gui.hpp"
#include "renderer/renderer.hpp"
#include "../input/input.hpp"
#include "../config.hpp"

#define ASSERT(x) \
if (!(x)) \
throw std::exception(#x)

namespace gui {
	void init() {
		ASSERT(glfwInit());

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
		glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		hWindow = glfwCreateWindow(640, 480, "KeyOverlay++", NULL, NULL);
		ASSERT(hWindow);

		glfwMakeContextCurrent(hWindow);
		glfwSwapInterval(1);

		ASSERT(ImGui::CreateContext());
		ASSERT(ImGui_ImplGlfw_InitForOpenGL(hWindow, true));
		ASSERT(ImGui_ImplOpenGL3_Init());

		ImGui::StyleColorsDark();
		ImGui::GetIO().IniFilename = NULL;

		ImGuiIO* io = &ImGui::GetIO();
		fonts.tahoma = io->Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Tahoma.ttf", 64);
	}

	bool loop() {
		if (glfwWindowShouldClose(hWindow))
			return true;

		glfwPollEvents();
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::SetNextWindowPos(ImVec2(-4, -1));
		ImGui::SetNextWindowSize(ImVec2(650, 490));
		ImGui::Begin("KeyOverlay++", nullptr, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
		{
			drawOverlay();
		}
		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		int nWidth, nHeight;
		glfwGetFramebufferSize(hWindow, &nWidth, &nHeight);
		glViewport(0, 0, nWidth, nHeight);
		glfwSwapBuffers(hWindow);

		return false;
	}

	void drawKeyLane(CKeyInput& key, int nTimes) {

		// filter out all keys that aren't this one
		std::vector<CKeyInput> vecThisKeyHistory;
		for (CKeyInput& itr : input::vecKeyHistory) {
			if (key.nKeyCode == itr.nKeyCode)
				vecThisKeyHistory.push_back(itr);
		}

		// calculate positions
		int nOffsetX;
		nOffsetX = 30 + ((50 + config::gui::nKeySpacing) * nTimes);

		// begin drawing the key square
		if (key.bHeld)
			renderer::drawRect(nOffsetX, 400, 50, 50, config::gui::nFillColor);

		renderer::drawRectOutline(nOffsetX, 400, 50, 50, 0, 5, config::gui::nOutlineColor);

		// draw the text
		char text = config::gui::bForceUppercase ? toupper(key.cKey) : key.cKey;

		if (config::gui::bIsVertical)
			fonts.tahoma->DrawStringVertical(nOffsetX + 25, 400 + 25, 24, config::gui::nOutlineColor, (const char*)&text);
		else
			fonts.tahoma->DrawChar(nOffsetX + 25, 400 + 25, 24, config::gui::nOutlineColor, text);
	}

	void drawOverlay() {
		// draw the key overlay itself
		int i = 0;
		for (CKeyInput& key : input::vecMonitoredKeys) {
			drawKeyLane(key, i);
			i++;
		}
	}

	void end() {
		ImGui_ImplGlfw_Shutdown();
		ImGui_ImplOpenGL3_Shutdown();

		ImGui::DestroyContext();

		glfwDestroyWindow(hWindow);
	}
}