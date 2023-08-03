#include "Powerup.h"

Powerup::Powerup(sf::Texture& texture, float speed, float initialX, float initialY) : speed(speed)
{
	sprite.setTexture(texture);
	sprite.setPosition(initialX, initialY);
	sprite.setScale(0.1f, 0.1f);
}

void Powerup::update(float deltaTime)
{
	sprite.move(speed * deltaTime, 0);
}

void Powerup::draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}

bool Powerup::contains(int x, int y)
{
	return sprite.getGlobalBounds().contains(x, y);
}
