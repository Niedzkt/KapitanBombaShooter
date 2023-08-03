#include "GameOverScene.h"
#include <iostream>

GameOverScene::GameOverScene(sf::RenderWindow& window) : Scene(window) {
    if (!backgroundImageTexture.loadFromFile("graphics/game_over.png")) {
        std::cout << "ERROR::GAMEOVERSCENE::BACKGROUND IMAGE FILE IS NOT LOADED" << std::endl;
    }
    backgroundImage.setTexture(backgroundImageTexture);

    if (!buttonFont.loadFromFile("fonts/button_font.ttf")) {
        std::cout << "ERROR::GAMEOVERSCENE::FONT FILE IS NOT LOADED" << std::endl;
    }

    restartButton.setFont(buttonFont);
    restartButton.setString("Restart");
    restartButton.setCharacterSize(24);
    restartButton.setPosition(sf::Vector2f(200, 200)); // ustaw odpowiedni¹ pozycjê

    menuButton.setFont(buttonFont);
    menuButton.setString("Menu");
    menuButton.setCharacterSize(24);
    menuButton.setPosition(sf::Vector2f(200, 250)); // ustaw odpowiedni¹ pozycjê
}

void GameOverScene::update(float deltaTime) {
    // logika aktualizacji sceny
}

void GameOverScene::draw() {
    window.draw(backgroundImage);
    window.draw(restartButton);
    window.draw(menuButton);
}

void GameOverScene::handleClick(int mouseX, int mouseY) {
    sf::Vector2f mousePos(mouseX, mouseY);
    if (restartButton.getGlobalBounds().contains(mousePos)) {
        // prze³¹cz na scenê gry
    }
    if (menuButton.getGlobalBounds().contains(mousePos)) {
        // prze³¹cz na scenê menu
    }
}
