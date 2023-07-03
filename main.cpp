#define WIN32_LEAN_AND_MEAN
#include "Engine.h"
#include <iostream>
#include "Utyls/System/FrameLimit.h"

#ifndef _DEBUG
int WINAPI wWinMain(HINSTANCE thisinst, HINSTANCE prevInst, PWSTR args, int cmdline) {
#else
int main() {
#endif
	CFrameLimiter frameLimit;
	frameLimit.setFPSLimit(60);
	GLFWwindow* mainWin = nullptr; // (ENGINE_WH, ENGINE_TITLE, sf::Style::Titlebar | sf::Style::Close);
	Game game(mainWin, &frameLimit);
	glfwSetTime(0);
	bool flag = false;
	while (!glfwWindowShouldClose(mainWin)) {
		glfwPollEvents();
		glClearColor(game.r, game.g, game.b, 0.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		if (frameLimit.onUpdate()) {

			if (!game.UpdateLogic()) {
				break;
			}

		}
		else {
			Sleep(10);
		}
		game.UpdateDraw();
		glfwSwapBuffers(mainWin);
	}
	glfwTerminate();
	return 0;
}
