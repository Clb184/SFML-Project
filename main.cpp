#include "Engine.h"

int main() {
	sf::RenderWindow mainWin(sf::VideoMode(640, 480), "SFML Engine", sf::Style::Titlebar | sf::Style::Close);

	mainWin.setFramerateLimit(60);

	Game game(&mainWin);

	while (mainWin.isOpen()) {
		sf::Event sfEvent;
		while (mainWin.pollEvent(sfEvent)) {
			if (sfEvent.type == sf::Event::Closed) {
				mainWin.close();
			}
		}
		mainWin.clear();
		game.Update();
		mainWin.display();
	}
	return 0;
}