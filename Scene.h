#pragma once

#include <SFML/Graphics.hpp>
#include "Game.h"


class Scene
{
protected:
	sf::RenderWindow& window;
	sf::View view;
public:
	Scene(sf::RenderWindow& window) : window(window) {}
	virtual void update(float deltaTime) = 0;
	virtual void draw() = 0;
	virtual void handleClick(int mouseX, int mouseY) = 0;
};

class MenuScene : public Scene {
public:
	MenuScene(sf::RenderWindow& window) : Scene(window) {}
	void update(float deltaTime) override;
	void draw() override;
	void handleClick(int mouseX, int mouseY) override;
};

class GameScene : public Scene {
private:
	Game game;
	sf::Texture monsterTexture;
	sf::Texture powerupTexture;
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;
	sf::Font font;
	sf::Shader shader;
public:
	GameScene(sf::RenderWindow& window);
	void update(float deltaTime) override;
	void draw() override;
	void handleClick(int mouseX, int mouseY) override;
	bool shouldSwitchToGameOver();
	void reset();
};

class GameOverScene : public Scene {
private:
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;
	sf::Font font;
	sf::Text menuButton;
	sf::Text restartButton;

public:
	GameOverScene(sf::RenderWindow& window);
	void update(float deltaTime) override;
	void draw() override;
	void handleClick(int mouseX, int mouseY) override;
	bool isRestartButtonClicked(int mouseX, int mouseY);
	bool isMenuButtonClicked(int mouseX, int mouseY);
};
