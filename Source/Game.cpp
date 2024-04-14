#include "Game.h"



bool redeploy = false;

void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(800,600), "Lost Viking", sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(60);
	this->window->setVerticalSyncEnabled(false);
}

void Game::initTextures()
{
	this->textures["BULLET"] = new sf::Texture();
	this->textures["BULLET"]->loadFromFile("Textures/Bullet.png");
}

void Game::initGUI()
{
	if (!(this->font.loadFromFile("Fonts/Dosis-Light.ttf")))
	{
		std::cout << "ERROR::GAME::FAILD TO LOAD FONT" << "\n";
	}

	this->pointText.setFont(this->font);
	this->pointText.setCharacterSize(20);
	this->pointText.setFillColor(sf::Color::White);
	this->pointText.setString("TEST");

	this->gameOverText.setFont(this->font);
	this->gameOverText.setCharacterSize(60);
	this->gameOverText.setFillColor(sf::Color::White);
	this->gameOverText.setString("GAME OVER!");
	this->gameOverText.setPosition(this->window->getSize().x / 2.f - this->gameOverText.getGlobalBounds().width / 2.f,
		this->window->getSize().y / 2 - this->gameOverText.getGlobalBounds().height / 2.f);

	this->playerHpBar.setSize(sf::Vector2f(300.f, 25.f));
	this->playerHpBar.setFillColor(sf::Color::Red);
	this->playerHpBar.setPosition(sf::Vector2f(20.f, 20.f));

	this->playerHpBarBack = this->playerHpBar;
	this->playerHpBarBack.setFillColor(sf::Color(25,15,15,200));
	this->playerHpBar.setPosition(sf::Vector2f(20.f, 20.f));
}

void Game::initWorld()
{
	if (!this->worldBackdroundTexture.loadFromFile("Textures/Background.jpg"))
	{
		std::cout << "ERROR::GAME::FAILD TO LOAD BACKGROUND" << "\n";
	}
	this->worldBackground.setTexture(this->worldBackdroundTexture);

	if (!this->worldBackdroundTexture1.loadFromFile("Textures/BlackScreen.png"))
	{
		std::cout << "ERROR::GAME::FAILD TO LOAD BACKGROUND_1" << "\n";
	}
	this->worldBackground1.setTexture(this->worldBackdroundTexture1);
}

void Game::initSystems()
{
	this->points = 0;
}

void Game::initPlayer()
{
	this->player = new Player();
}

void Game::initEnemies()
{
	this->spawnTimerMax = 30.f;
	this->spawnTime = this->spawnTimerMax;
}

Game::Game()
{
	this->initWindow();
	this->initTextures();
	this->initGUI();
	this->initWorld();
	this->initSystems();
	this->initPlayer();
	this->initEnemies();
}

Game::~Game()
{
	delete this->window;
	delete this->player;

	for (auto &i : this->textures)
	{
		delete i.second;
	}

	for (auto *i : this->bullets)
	{
		delete i;
	}

	for (auto *i : this->enemies)
	{
		delete i;
	}
}

void Game::run()
{
	while (this->window->isOpen())
	{
		this->updatePollEvents();
		if (this->player->getHp() > 0)
		{
			this->update();
		}
		this->render();
	}
}

void Game::updatePollEvents()
{
	sf::Event e;
	while (this->window->pollEvent(e))
	{
		if (e.Event::type == sf::Event::Closed)
		{
			this->window->close();
		}
		if (e.Event::KeyPressed && e.Event::key.code == sf::Keyboard::Escape)
		{
			this->window->close();
		}
	}
}

void Game::updateInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		this->player->move(-1.f, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		this->player->move(1.f, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		this->player->move(0.f, -1.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		this->player->move(0.f, 1.f);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		this->player->move(-1.f, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		this->player->move(1.f, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		this->player->move(0.f, -1.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		this->player->move(0.f, 1.f);
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->player->canAttack())
	{
		this->bullets.push_back(new Bullet(this->textures["BULLET"],
			this->player->getPos().x + this->player->getBounds().width/2.f,
			this->player->getPos().y,0.f,-1.f,5.f));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F) && this->player->canAttack())
	{
		this->bullets.push_back(new Bullet(this->textures["BULLET"],
			this->player->getPos().x + this->player->getBounds().width / 2.f,
			this->player->getPos().y, 0.f, -1.f, 5.f));
	}
}

void Game::updateGUI()
{
	std::stringstream ss;

	ss << "Points " << this->points;

	this->pointText.setString(ss.str());

	float hpPercent = static_cast<float>(this->player->getHp())/this->player->getHpMax();
	this->playerHpBar.setSize(sf::Vector2f(300.f * hpPercent, this->playerHpBar.getSize().y));
}

void Game::updateWorld()
{

}

void Game::updateCollisison()
{
	if (this->player->getBounds().left < -20.f)
	{
		this->player->setPosition(-20.f, this->player->getBounds().top);
	}
	else if (this->player->getBounds().left + this->player->getBounds().width >= this->window->getSize().x + 20.f)
	{
		this->player->setPosition(this->window->getSize().x - this->player->getBounds().width + 20.f, this->player->getBounds().top);
	}

	if (this->player->getBounds().top < -10.f)
	{
		this->player->setPosition(this->player->getBounds().left, -10.f);
	}
	else if (this->player->getBounds().top + this->player->getBounds().height >= this->window->getSize().y + 10.f)
	{
		this->player->setPosition(this->player->getBounds().left, this->window->getSize().y - this->player->getBounds().height + 10.f);
	}
}

void Game::updateBullets()
{
	unsigned counter = 0;
	for (auto *bullet : this->bullets)
	{
		bullet->update();

		if (bullet->getBounds().top + bullet->getBounds().height < 0.f)
		{
			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin() + counter);
			--counter;
		}

		++counter;
	}
}

void Game::updateEnemies()
{
	this->spawnTime += 1.f;
	if (this->spawnTime >= this->spawnTimerMax)
	{
		this->enemies.push_back(new Enemy(rand() % this->window->getSize().x - 20.f, -100.f));
		this->spawnTime = 0.f;
	}

	unsigned counter = 0;
	for (auto *enemy : this->enemies)
	{
		enemy->update();

		if (enemy->getBounds().top > this->window->getSize().y)
		{
			delete this->enemies.at(counter);
			this->enemies.erase(this->enemies.begin() + counter);
			--counter;
			std::cout << this->enemies.size() << "\n";
		}
		else if (enemy->getBounds().intersects(this->player->getBounds()))
		{
			this->player->loseHp(this->enemies.at(counter)->getDamage());
			delete this->enemies.at(counter);
			this->enemies.erase(this->enemies.begin() + counter);
			--counter;
			
		}

		++counter;
	}
}

void Game::updateCombat()
{
	for (int i = 0; i < this->enemies.size(); ++i)
	{
		bool enemy_removed = false;
		for (size_t k = 0; k < this->bullets.size() && enemy_removed == false; k++)
		{
			if (this->enemies[i]->getBounds().intersects(this->bullets[k]->getBounds()))
			{
				this->points += this->enemies[i]->getPoints();

				std::cout << "hit" << "\n";

				delete this->enemies[i];
				this->enemies.erase(this->enemies.begin() + i);
				enemy_removed = true;

				delete this->bullets[k];
				this->bullets.erase(this->bullets.begin() + k);
			}
		}
	}
}

void Game::update()
{
	//this->updatePollEvents();

	this->updateInput();

	this->player->update();

	this->updateCollisison();

	this->updateBullets();

	this->updateEnemies();

	this->updateCombat();

	this->updateGUI();

	this->updateWorld();
}

void Game::renderGUI()
{
	this->window->draw(this->pointText);

	this->window->draw(this->playerHpBarBack);
	this->window->draw(this->playerHpBar);
}

void Game::renderWorld()
{
	this->window->draw(this->worldBackground);
}

void Game::render()
{
	this->window->clear();

	this->renderWorld();

	this->player->render(*this->window);
	if (redeploy == false)
	{
		this->player->setPosition(400.f, 300.f);
		redeploy = true;
	}

	for (auto *bullet : this->bullets)
	{
		bullet->render(this->window);
	}

	for (auto *enemy : this->enemies)
	{
		enemy->render(this->window);
	}

	this->renderGUI();

	if (this->player->getHp() <= 0)
	{
		this->window->draw(this->worldBackground1);
		this->window->draw(this->gameOverText);
	}

	this->window->display();
}
