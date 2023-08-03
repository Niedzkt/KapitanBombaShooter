#pragma once

#include <SFML/Graphics.hpp>

class Entity
{
protected:
	sf::Sprite sprite;

public:
	virtual void update(float deltaTime) = 0;
	virtual void draw(sf::RenderWindow& window) = 0;
};

