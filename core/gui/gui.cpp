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

		std::string strFontPath = config::file["text"]["font"].get<std::string>();
		pFont = io->Fonts->AddFontFromFileTTF(R"(C:\Windows\Fonts\Tahoma.ttf)", 64);
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
		int nSize = config::file["keyBox"]["size"].get<int>();
		int nScrollSpeed = config::file["history"]["scrollSpeed"].get<int>();

		if (!key.bWasHeld && key.bHeld)
			key.deqKeyHistory.emplace_front().dEnd = 450 - nSize;

		for (int i = 0; i < key.deqKeyHistory.size(); i++) {
			CKeyInput& current = key.deqKeyHistory.at(i);

			double dStepAmount = nScrollSpeed * ImGui::GetIO().DeltaTime;
			current.dStart -= dStepAmount;
			current.dEnd -= dStepAmount;

			if (i == 0 && key.bHeld) {
				current.dStart = 450 - nSize;
			}
		}

		// remove records above the area
		key.deqKeyHistory.erase(
			std::remove_if(key.deqKeyHistory.begin(), key.deqKeyHistory.end(), [](const CKeyInput& in) { return in.dStart <= 0; }
		), key.deqKeyHistory.end());

		key.bWasHeld = key.bHeld;
	}

	void drawKeyLane(CKey& key, int nTimes) {
		int nSize = config::file["keyBox"]["size"].get<int>();

		int nFillColor = config::file["colors"]["fill"].get<int>();
		int nHistoryColor = config::file["colors"]["history"].get<int>();
		int nOutlineColor = config::file["colors"]["outline"].get<int>();
		int nTextColor = config::file["colors"]["text"].get<int>();

		int nOffsetX = 30 + ((nSize + config::file["keyBox"]["spacing"]) * nTimes);

		// draw box
		if (key.bHeld)
			renderer::drawRect(nOffsetX, 450 - nSize, nSize, nSize, nFillColor);

		renderer::drawRectOutline(nOffsetX, 450 - nSize, nSize, nSize, 0, config::file["keyBox"]["outlineThickness"].get<int>(), nOutlineColor);
		
		// draw history
		if (config::file["history"]["enabled"].get<bool>()) {
			for (CKeyInput& input : key.deqKeyHistory) {
				// fade
				if (config::file["history"]["fadeOut"].get<bool>()) {
					int nFadeDistance = config::file["history"]["fadeDistance"].get<int>();

					int nDistanceFromFade = nFadeDistance - input.dStart;

					int nOriginalAlpha = (nHistoryColor >> 24) & 0xFF;
					int nColor = nHistoryColor;

					float fScale = (float)std::clamp(nDistanceFromFade, 0, 100) / 100.f;
					int nNewAlpha = (int)nOriginalAlpha * (1 - fScale);

					nColor = nNewAlpha << 24 | ((nColor >> 16) & 0xFF) << 16 | ((nColor >> 8) & 0xFF) << 8 | nColor & 0xFF;
					std::cout << ((nColor >> 24) & 0xFF) << std::endl;

					renderer::drawRect(nOffsetX, input.dStart, nSize, input.dEnd - input.dStart, nColor);
				}
				else {
					renderer::drawRect(nOffsetX, input.dStart, nSize, input.dEnd - input.dStart, nHistoryColor);
				}
			}
		}

		// draw text
		char text = config::file["text"]["forceUppercase"].get<bool>() ? toupper(key.cKey) : key.cKey;
		if (config::file["text"]["vertical"].get<bool>())
			pFont->DrawStringVertical(nOffsetX + (nSize / 2), 450 - (nSize / 2), 24 * (nSize / 50), nTextColor, (const char*)&text);
		else
			pFont->DrawChar(nOffsetX + (nSize / 2), 450 - (nSize / 2), 24 * (nSize / 50), nTextColor, text);
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