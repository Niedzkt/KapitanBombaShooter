#include "Scene.h"
#include <iostream>

using namespace std;

void MenuScene::update(float deltaTime)
{
}

void MenuScene::draw()
{
}

void MenuScene::handleClick(int mouseX, int mouseY)
{
}


GameScene::GameScene(sf::RenderWindow& window) : Scene(window), game(monsterTexture, powerupTexture, font)
{
	view.setSize(window.getSize().x, window.getSize().y);
	view.setCenter(window.getSize().x / 2.0f, window.getSize().y / 2.0f);


	if (!monsterTexture.loadFromFile("graphics/enemy.png")) {
		cout << "ERROR::TEXTURE ENEMY FILE IS NOT LOADED" << std::endl;
	}

	if (!powerupTexture.loadFromFile("graphics/powerup.png")) {
		cout << "ERROR::TEXTURE POWER_UP FILE IS NOT LOADED" << std::endl;
	}

	if (!font.loadFromFile("fonts/font.ttf")) {
		cout << "ERROR::FONT FILE IS NOT LOADED" << std::endl;
	}

	if (!shader.loadFromFile("shaders/blurShader.glsl", sf::Shader::Fragment))
	{
		cout << "ERROR::FRAGMENT SHADER FILE IS NOT LOADED" << std::endl;
	}
	if (!backgroundTexture.loadFromFile("graphics/background.png")) {
		cout << "ERROR::BACKGROUND TEXTURE FILE IS NOT LOADED" << endl;
	}

	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite.setScale(1.5, 1.5);

}

void GameScene::update(float deltaTime)
{
	game.update(deltaTime);
}

void GameScene::draw()
{
	window.setView(view);
	if (game.getPowerupCounterView() == 1) {
		cout << "Shader is working" << endl;
		//sf::Shader::bind(&shader);
		game.shakeView();
	}
	window.draw(backgroundSprite);
	game.draw(window);
	sf::Shader::bind(NULL);
	window.setView(window.getDefaultView());
}

void GameScene::handleClick(int mouseX, int mouseY)
{
	game.handleClick(mouseX, mouseY);
}

bool GameScene::shouldSwitchToGameOver()
{
	bool result = game.isMonsterOnScreenTooLong();
	if (result) {
		std::cout << "Switching to GameOverScene..." << std::endl;
	}
	return result;
}

void GameScene::reset()
{
	game.reset();
}

GameOverScene::GameOverScene(sf::RenderWindow& window) : Scene(window)
{
	view.setSize(window.getSize().x, window.getSize().y);
	view.setCenter(window.getSize().x / 2.0f, window.getSize().y / 2.0f);

	if (!backgroundTexture.loadFromFile("graphics/gameover.png")) {
		cout << "ERROR::TEXTURE GAMEOVER FILE IS NOT LOADED" << endl;
	}

	backgroundSprite.setTexture(backgroundTexture);

	if (!font.loadFromFile("fonts/font.ttf")) {
		cout << "ERROR::FONT FILE IS NOT LOADED" << endl;
	}

	menuButton.setFont(font);
	menuButton.setString("MENU");
	menuButton.setCharacterSize(24);
	menuButton.setFillColor(sf::Color::White);
	menuButton.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);

	restartButton.setFont(font);
	restartButton.setString("RESTART");
	restartButton.setCharacterSize(24);
	restartButton.setFillColor(sf::Color::White);
	restartButton.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f + 50);
}

void GameOverScene::update(float deltaTime)
{
}

void GameOverScene::draw()
{
		window.setView(view);
		//cout << "GameScene draw method called." << endl;
		window.draw(backgroundSprite);
		window.draw(menuButton);
		window.draw(restartButton);
}

void GameOverScene::handleClick(int mouseX, int mouseY)
{
}

bool GameOverScene::isRestartButtonClicked(int mouseX, int mouseY)
{
	sf::FloatRect buttonBounds = restartButton.getGlobalBounds();
	return buttonBounds.contains(mouseX, mouseY);
}

bool GameOverScene::isMenuButtonClicked(int mouseX, int mouseY)
{
	sf::FloatRect buttonBounds = menuButton.getGlobalBounds();
	return buttonBounds.contains(mouseX, mouseY);
}
