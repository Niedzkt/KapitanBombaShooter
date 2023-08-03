#include "Game.h"
#include <iostream>
#include <ctime>

using namespace std;

Game::Game(sf::Texture& monsterTexture, sf::Texture& powerupTexture, sf::Font& font) 
: monsterTexture(monsterTexture),
powerupTexture(powerupTexture),
font(font),
view(view),
monsterCounter(0),
monsterSpawnCounter(0),
spawnTime(1.0f),
powerupCounter(0),
powerupSpawnCounter(0),
spawnTimePowerUp(15.0f),
monsterLimit(5.0f),
initialMonsterSpeed(100.0f), // Tu dodajesz pocz¹tkow¹ prêdkoœæ potwora
initialSpawnTime(3.0f), // Tu dodajesz pocz¹tkowy czas generowania potwora
initialSpawnTimePowerUp(15.0f) // Tu dodajesz pocz¹tkowy czas generowania powerup'ów

{
	clock.restart();

	monsterCounterText.setFont(font);
	monsterCounterText.setCharacterSize(24);
	monsterCounterText.setFillColor(sf::Color::White);
	monsterCounterText.setPosition(0, 10);

	powerupCounterText.setFont(font);
	powerupCounterText.setCharacterSize(24);
	powerupCounterText.setFillColor(sf::Color::White);
	powerupCounterText.setPosition(560, 10);


	spawnMonster();

	spawnPowerup();

	view.setCenter(400, 300);
	view.setSize(800, 600);
}

void Game::spawnMonster()
{
	int monsterCount = rand() % 3 + 1;

	for (int i = 0; i < monsterCount; i++) {
		//random spawn X and Y position
		float x = static_cast<float>(rand() % 600);
		float y = static_cast<float>(rand() % 400);

		monsters.emplace_back(monsterTexture, monsterSpeed, x, y);
	}
}


void Game::spawnPowerup()
{
	float x = static_cast<float>(rand() % 800);
	float y = static_cast<float>(rand() % 600);

	powerups.emplace_back(powerupTexture, 1.0f, x, y);
}

void Game::update(float deltaTime)
{
	monsterSpawnCounter += deltaTime;

	if (monsterSpawnCounter >= spawnTime) {
		spawnMonster();
		monsterSpawnCounter = 0;
		spawnTime = 1.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (3.0f - 1.0f))); // Random time between 1 and 3
		if (monsterCounter >= 50) {
			spawnTime = 1.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (2.0f - 1.0f))); // Random time between 1 and 2
		}
		if (monsterCounter >= 100) {
			spawnTime = 0.5f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (2.0f - 1.0f))); // Random time between 1 and 2
		}
		if (monsterCounter >= 200) {
			spawnTime = 0.2f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (2.0f - 1.0f))); // Random time between 1 and 2
		}
	}

	for (auto& monster : monsters) {
		monster.update(deltaTime);
	}

	/*if (powerupCounterView >= 1) {
		shakeView();
		window.setView(view);
	}*/

	powerupSpawnCounter += deltaTime;

	if (powerupSpawnCounter >= spawnTimePowerUp) {
		spawnPowerup();
		powerupSpawnCounter = 0;
	}

	for (auto& powerup : powerups) {
		powerup.update(deltaTime);
	}

	monsterCounterText.setString("Ustrzeleni Kosmici: " + to_string(static_cast<int>(monsterCounter)));
	powerupCounterText.setString(to_string(static_cast<int>(powerupCounterView))+ " :Drink Ojca Pijo");
}

void Game::draw(sf::RenderWindow& window)
{
	if (powerupCounterView >= 1) {
		shakeView();
		window.setView(view);
	}
	for (Monster& monster : monsters) {
		monster.draw(window);
	}

	for (Powerup& powerup : powerups) {
		powerup.draw(window);
	}

	window.draw(monsterCounterText);
	window.draw(powerupCounterText);

	window.setView(window.getDefaultView());
}

void Game::handleClick(int mouseX, int mouseY)
{
	for (auto it = monsters.begin(); it != monsters.end(); ) {
		if (it->contains(mouseX, mouseY)) {
			it = monsters.erase(it);
			monsterCounter++;
			monsterTimeOnScreen = 0; // Reset the time a monster has been on screen
			if (static_cast<int>(monsterCounter) % 10 == 0 && spawnTime > 0.1f) {
				spawnTime -= 0.2f;
				if (spawnTime < 0.1f) {
					spawnTime = 0.1f;
				}
				monsterSpeed += 20.f;
			}
			break;
		}
		else {
			++it;
		}
	}

	for (auto it = powerups.begin(); it != powerups.end();) {
		if (it->contains(mouseX, mouseY)) {
			it = powerups.erase(it);
			powerupCounter++;
			if (static_cast<int>(powerupCounter) % 1 == 0) {
				cout << "zaraz sie najebiesz" << endl;
				powerupCounterView = powerupCounter / 1;
			}
		}
		else {
			++it;
		}
	}
}

bool Game::isMonsterOnScreenTooLong()
{
	for (const auto& monster : monsters) {
		if (monster.getTimeOnScreen() > monsterLimit) {  // Sprawdzamy czas ka¿dego potwora
			cout << "Monster on screen too long..." << std::endl;
			return true;
		}
	}
	return false;
}

void Game::reset() {
	cout << "Reset method called." << endl;
	monsters.clear();
	powerups.clear();
	monsterCounter = 0;
	monsterSpawnCounter = 0;
	powerupCounter = 0;
	powerupSpawnCounter = 0;
	monsterSpeed = initialMonsterSpeed;  // mo¿esz chcieæ przechowywaæ pocz¹tkow¹ prêdkoœæ potwora
	spawnTime = initialSpawnTime;  // to samo dla czasu generowania potwora
	spawnTimePowerUp = initialSpawnTimePowerUp;  // to samo dla czasu generowania powerup'ów

	spawnMonster();
	spawnPowerup();
}

void Game::shakeView()
{
	cout << "shakeView working" << endl;
	float amplitude = 1.0f; // Amplituda ko³ysania
	float frequency = 0.50f; // Czêstotliwoœæ ko³ysania
	float time = clock.getElapsedTime().asSeconds(); // Czas gry

	// Obliczamy now¹ pozycjê X dla widoku kamery
	float newX = view.getCenter().x + amplitude * sin(2.0f * 3.14159f * frequency * time);

	// Ustawiamy now¹ pozycjê dla widoku kamery
	view.setCenter(newX, view.getCenter().y);
}

int Game::getPowerupCounterView()
{
	return powerupCounterView;
}
