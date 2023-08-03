#pragma once

#include <SFML/Graphics.hpp>
#include "Scene.h"

class GameOverScene : public Scene {
private:
    sf::Texture backgroundImageTexture;
    sf::Sprite backgroundImage;
    sf::Font buttonFont;
    sf::Text restartButton;
    sf::Text menuButton;

public:
    GameOverScene(sf::RenderWindow& window);
    void update(float deltaTime) override;
    void draw() override;
    void handleClick(int mouseX, int mouseY);
};