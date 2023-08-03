#pragma once

#include "Entity.h"

class Monster : public Entity
{
private:
	float speed;
	sf::Sprite sprite;
	float dx, dy;
	float timeOnScreen;
public:

	static float screenWidth;
	static float screenHeight;

	Monster(sf::Texture& texture, float speed, float initialX, float initialY);
	void update(float deltaTime) override;
	void draw(sf::RenderWindow& window) override;
	bool contains(int x, int y);

	float getTimeOnScreen() const { return timeOnScreen; }
};

