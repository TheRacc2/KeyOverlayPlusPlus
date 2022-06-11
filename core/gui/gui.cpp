#include "gui.hpp"
#include "renderer/renderer.hpp"
#include "../input/input.hpp"
#include "../config/config.hpp"

#include <iostream>

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

	void updateKeyLane(CKey& key) {
		if (!key.bWasHeld && key.bHeld)
			key.deqKeyHistory.emplace_front().dEnd = 450 - config::gui::nSize;

		for (int i = 0; i < key.deqKeyHistory.size(); i++) {
			CKeyInput& current = key.deqKeyHistory.at(i);

			double dStepAmount = config::gui::nScrollSpeed * ImGui::GetIO().DeltaTime;
			current.dStart -= dStepAmount;
			current.dEnd -= dStepAmount;

			if (i == 0 && key.bHeld) {
				current.dStart = 450 - config::gui::nSize;
			}
		}

		key.deqKeyHistory.erase(
			std::remove_if(key.deqKeyHistory.begin(), key.deqKeyHistory.end(), [](const CKeyInput& in) { return in.dStart <= 0; }
		), key.deqKeyHistory.end());
		key.bWasHeld = key.bHeld;
	}

	void drawKeyLane(CKey& key, int nTimes) {
		int nOffsetX = 30 + ((config::gui::nSize + config::gui::nKeySpacing) * nTimes);

		// draw box
		if (key.bHeld)
			renderer::drawRect(nOffsetX, 450 - config::gui::nSize, config::gui::nSize, config::gui::nSize, config::gui::nFillColor);

		renderer::drawRectOutline(nOffsetX, 450 - config::gui::nSize, config::gui::nSize, config::gui::nSize, 0, 3, config::gui::nOutlineColor);
		
		// draw history
		for (CKeyInput& input : key.deqKeyHistory) {
			// fade
			if (config::gui::bFadeOut) {
				int nDistanceFromFade = config::gui::nFadeDistance - input.dStart;

				int nOriginalAlpha = (config::gui::nFillColor >> 24) & 0xFF;
				int nColor = config::gui::nFillColor;

				float fScale = (float)std::clamp(nDistanceFromFade, 0, 100) / 100.f;
				int nNewAlpha = (int)nOriginalAlpha * (1 - fScale);

				nColor = nNewAlpha << 24 | ((nColor >> 16) & 0xFF) << 16 | ((nColor >> 8) & 0xFF) << 8 | nColor & 0xFF;
				std::cout << ((nColor >> 24) & 0xFF) << std::endl;

				renderer::drawRect(nOffsetX, input.dStart, config::gui::nSize, input.dEnd - input.dStart, nColor);
			}
			else {
				renderer::drawRect(nOffsetX, input.dStart, config::gui::nSize, input.dEnd - input.dStart, config::gui::nFillColor);
			}
		}

		// draw text
		char text = config::gui::bForceUppercase ? toupper(key.cKey) : key.cKey;
		fonts.tahoma->DrawChar(nOffsetX + (config::gui::nSize / 2), 450 - (config::gui::nSize / 2), 24 * (config::gui::nSize / 50), config::gui::nOutlineColor, text);
	}

	void drawOverlay() {
		// draw the key overlay itself
		
		for (int i = 0; i < input::vecMonitoredKeys.size(); i++) {
			CKey& key = input::vecMonitoredKeys.at(i);

			updateKeyLane(key);
			drawKeyLane(key, i);
		}
	}

	void end() {
		ImGui_ImplGlfw_Shutdown();
		ImGui_ImplOpenGL3_Shutdown();

		ImGui::DestroyContext();

		glfwDestroyWindow(hWindow);
	}
}