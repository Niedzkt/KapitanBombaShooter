#pragma once

#include "Entity.h"

class Powerup: public Entity
{
private:
	float speed;
	sf::Sprite sprite;
	bool isClicked;

public:
	Powerup(sf::Texture& texture, float speed, float initialX, float initialY);
	void update(float deltaTime) override;
	void draw(sf::RenderWindow& window) override;
	bool contains(int x, int y);
};

