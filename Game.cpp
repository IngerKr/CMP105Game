#include "Game.h"

sf::Music music;

//Private functions
void Game::initVariables()
{
	this->window = nullptr;

	//Game logic
	this->endGame = false;
	this->points = 0;
	this->health = 10;
	this->enemySpawnTimerMax = 25.f;
	this->enemySpawnTimer = enemySpawnTimerMax;
	this->maxEnemies = 6;
	this->mouseHeld = false;

}

void Game::initWindow()
{
	this->videoMode.height = 600;
	this->videoMode.width = 800;

	this->window = new sf::RenderWindow(this->videoMode, "GameName", sf::Style::Titlebar | sf::Style::Close);

	this->window->setFramerateLimit(60);
}

void Game::initFonts()
{
	this->font.loadFromFile("Fonts/Gronzy-Regular.ttf");
	/*if (!this->font.loadFromFile("Fonts/Gronzy-Regular.ttf"))
	{
		std::cout << "Failed to load font!\n";
	}*/

	
}

void Game::initText()
{
	this->gameText.setFont(this->font);
	this->gameText.setCharacterSize(24);
	this->gameText.setFillColor(sf::Color::White);
	/*this->gameText.setPosition(200, 400);*/
}

void Game::initEnemies()
{
	this->enemy.setPosition(10.f, 10.f);
	this->enemy.setSize(sf::Vector2f(100.f, 100.f));
	this->enemy.setScale(sf::Vector2f(0.5f, 0.5f));
	this->enemy.setFillColor(sf::Color::Cyan);
	//this->enemy.setOutlineColor(sf::Color::Green);
	//this->enemy.setOutlineThickness(1.f);


}

//Constructors / destructors

Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initFonts();
	this->initText();
	this->initEnemies();
}

Game::~Game()
{
	delete this->window;
}


//Accessors
const bool Game::running() const
{
	return this->window->isOpen();
}

const bool Game::getEndGame() const
{
	return this->endGame;
}

//Functions

void Game::spawnEnemy()
{
	//Sets enemy into position
	this->enemy.setPosition(
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
		0.f
	);

	this->enemy.setFillColor(sf::Color::Green);

	//spawn the enemy
	this->enemies.push_back(this->enemy);

}

void Game::pollEvents()
{
	//Event polling
	while (this->window->pollEvent(this->event))
	{
		switch (this->event.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->event.key.code == sf::Keyboard::Escape)
				/*this->escScreen();*/
				break;
		case sf::Event::Resized:
			this->window->setView(sf::View(sf::FloatRect(0.f, 0.f, (float)event.size.width, (float)event.size.height)));
		}
	}
}

void Game::updateMousePositions()
{
	/*
	return void

	updates the mouse positions
		- mouse position relative to window(vector2i)
	*/

	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::updateText()
{
	std::stringstream ss;

	ss << "Points: " << this->points << "\n" << "Health: " << this->health << "\n";

	this->gameText.setString(ss.str());
	/*this->gameText.setString("Hello world");*/
}

void Game::updateEnemies()
{
	/*
	return void

	updates the enemy spawn timer and spawns enemies when the total amount of enemies is smaller than the max

	moves the enemies downwards

	removes the enemies at the edge of the screen //TODO
	*/


	//updating the timer for enemy spawning
	if (this->enemies.size() < this->maxEnemies)
	{
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
		{
			//spawn the enemy and reset the timer
			this->spawnEnemy();
			this->enemySpawnTimer = 0.f;
		}
		else
		{
			this->enemySpawnTimer += 1.f;
		}
	}

	//moving and updating enemies
	for (int i = 0; i < this->enemies.size(); i++)
	{
		bool deleted = false;

		this->enemies[i].move(0.f, 5.f);

		if (this->enemies[i].getPosition().y > this->window->getSize().y)
		{
			this->enemies.erase(this->enemies.begin() + i);
			this->health -= 1;
			//setting a sound when enemy reaches bottom of screen, and a healthpoint is lost
			music.openFromFile("1891.ogg");
			music.play();
		}
	}

	//check if clicked upon
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (this->mouseHeld == false)
		{
			this->mouseHeld = true;
			bool deleted = false;
			for (size_t i = 0; i < this->enemies.size() && deleted == false; i++)
			{
				if (this->enemies[i].getGlobalBounds().contains(this->mousePosView))
				{
					//delete the enemy
					deleted = true;
					this->enemies.erase(this->enemies.begin() + i);

					//gain points
					this->points += 1;
					//Setting a sound for when an enemy is clicked and a point is gained
					music.openFromFile("1895.ogg");
					music.play();
				}
			}
		}
	}
	else
	{
		this->mouseHeld = false;
	}

}

void Game::update()
{
	this->pollEvents();

	if (this->endGame == false)
	{
		this->updateMousePositions();

		this->updateText();

		this->updateEnemies();
	}

	//endgame condition - currently closes game
	if (this->health <= 0)
	{
		this->endGame = true;
	}

}

void Game::renderText()
{
	this->window->draw(this->gameText);
}

void Game::renderEnemies()
{
	//rendering all the enemies
	for (auto& e : this->enemies)
	{
		this->window->draw(e);
	}
}


void Game::render()
{
	/*
	@return void

	-clear old frame
	-render objects
	-display frame in window

	renders game objects.
	*/

	this->window->clear();

	//Draw game objects
	this->renderEnemies();

	this->renderText();

	this->window->display();
}

//void Game::startScreen()
//{
//	this->window->clear();
//
//	//Show controls
//
//	//Show "PLAY" option
//
//	this->window->display();
//}
//
//void Game::escScreen()
//{
//	this->window->clear();
//
//	//Show options
//
//	this->window->display();
//}

