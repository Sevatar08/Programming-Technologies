#pragma once
#include <map>
#include <string>
#include <sstream>
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"

class Game
{
private:
	sf::RenderWindow* window;

	std::map<std::string, sf::Texture*> textures;
	std::vector<Bullet*> bullets;

	sf::Font font;
	sf::Text pointText;
	sf::Text gameOverText;

	sf::Texture worldBackdroundTexture;
	sf::Sprite worldBackground;

	sf::Texture worldBackdroundTexture1;
	sf::Sprite worldBackground1;

	unsigned points;

	Player* player;

	sf::RectangleShape playerHpBar;
	sf::RectangleShape playerHpBarBack;

	float spawnTime;
	float spawnTimerMax;
	std::vector<Enemy*> enemies;

	void initWindow();
	void initTextures();
	void initGUI();
	void initWorld();
	void initSystems();

	void initPlayer();
	void initEnemies();

public:
	Game();
	virtual ~Game();

	void run();

	void updatePollEvents();
	void updateInput();
	void updateGUI();
	void updateWorld();
	void updateCollisison();
	void updateBullets();
	void updateEnemies();
	void updateCombat();
	void update();
	void renderGUI();
	void renderWorld();
	void render();
};

