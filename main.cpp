#include <iostream>
#include <SFML/Graphics.hpp>
#include "Scene.h"

using namespace std;

int main() {

	sf::RenderWindow window(sf::VideoMode(800, 600), "Game");

	//MenuScene menuScene(window);
	GameScene gameScene(window);
	GameOverScene gameOverScene(window);
	Scene* currentScene = &gameOverScene;

	sf::Clock clock;

	while (window.isOpen()) {
		float deltaTime = clock.restart().asSeconds();

		currentScene->update(deltaTime);

		if (currentScene == &gameScene && gameScene.shouldSwitchToGameOver()) {
			currentScene = &gameOverScene;
			continue;
		}
		window.setView(window.getDefaultView());
		window.clear();
		currentScene->draw();
		window.display();

		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left) {
					currentScene->handleClick(event.mouseButton.x, event.mouseButton.y);
					if (currentScene == &gameOverScene && gameOverScene.isRestartButtonClicked(event.mouseButton.x, event.mouseButton.y)) {
						cout << "Restart button clicked." << endl;
						gameScene.reset();
						currentScene = &gameScene;
					}
				}
				break;
			}
		}
	}

	return 0;
}