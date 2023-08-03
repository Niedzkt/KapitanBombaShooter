#pragma once
#include <vector>
#include "Monster.h"
#include "Powerup.h"

using namespace std;

class Game
{
private:
	sf::Texture& monsterTexture;
	sf::Texture& powerupTexture;

	sf::Font& font;
	sf::View view;
	sf::Clock clock;

	sf::Text monsterCounterText;
	sf::Text powerupCounterText;

	vector<Monster> monsters;
	vector<Powerup> powerups;

	float monsterCounter;
	float monsterSpawnCounter;
	float spawnTime;
	float monsterTimeOnScreen;
	float monsterLimit;

	float powerupCounter;
	float powerupCounterView;
	float powerupSpawnCounter;
	float spawnTimePowerUp;

	float monsterSpeed;

	float initialMonsterSpeed;
	float initialSpawnTime;
	float initialSpawnTimePowerUp;

public:
	Game(sf::Texture& monsterTexture, sf::Texture& powerupTexture, sf::Font& font);
	void spawnMonster();
	void spawnPowerup();
	void update(float deltaTime);
	void draw(sf::RenderWindow& window);
	void handleClick(int mouseX, int mouseY);
	bool isMonsterOnScreenTooLong();
	void reset();
	void shakeView();
	int getPowerupCounterView();
};