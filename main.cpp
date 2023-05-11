#include "Engine.h"


int main() {
	sf::RenderWindow mainWin; // (ENGINE_WH, ENGINE_TITLE, sf::Style::Titlebar | sf::Style::Close);
	//sf::View cutView;
	//cutView.setCenter((1280.0f / 1.5f) / 2, 240.0f);
	//cutView.setSize(1280.0f / 1.5f, 480.0f);

	//mainWin.setView(cutView);
	//mainWin.setFramerateLimit(60);

	Game game(&mainWin);
	while (mainWin.isOpen()) {
		sf::Event sfEvent;
		while (mainWin.pollEvent(sfEvent)) {
			if (sfEvent.type == sf::Event::Closed) {
				mainWin.close();
				
				//exit(0);
			}
		}

		//mainWin.clear();
		if (!game.UpdateLogic()) {
			mainWin.close();
			//exit(0);
		}
		if (mainWin.hasFocus()) {
			game.UpdateDraw();
			mainWin.display();
		}
		//Sleep(12);
		//game.m_ScreenCap.update(mainWin);
	}
	return 0;
}
