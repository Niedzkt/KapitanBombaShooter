#include "Monster.h"

float Monster::screenHeight = 600.0f;
float Monster::screenWidth = 800.0f;

Monster::Monster(sf::Texture& texture, float speed, float initialX, float initialY) :speed(speed), dx(1.0f), dy(1.0f), timeOnScreen(0.0f)
{
	sprite.setTexture(texture);
	sprite.setPosition(initialX, initialY);
	sprite.setScale(0.5, 0.5);

}

void Monster::update(float deltaTime)
{
	float newX = sprite.getPosition().x + dx * speed * deltaTime;
	float newY = sprite.getPosition().y + dy * speed * deltaTime;

	if (newX < 0 || newX + sprite.getGlobalBounds().width > 800) {
		dx = -dx;
		newX = sprite.getPosition().x;
	}

	if (newY < 0 || newY + sprite.getGlobalBounds().height > 600) {
		dy = -dy;
		newY = sprite.getPosition().y;
	}

	sprite.setPosition(newX, newY);

	timeOnScreen += deltaTime;

}

void Monster::draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}

bool Monster::contains(int x, int y)
{
	return sprite.getGlobalBounds().contains(x, y);
}
