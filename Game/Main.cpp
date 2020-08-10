#include <iostream>
#include "Game.h"

//sf::Clock clock;
//float deltaTime;

int main()
{
	//calculate delta time
	//deltaTime = clock.restart().asSeconds();

	//Init srand
	//std::srand(static_cast<unsigned>(time(NULL)));

	//Init game engine
	Game game;

	while (game.running())
	{


		//Update
		game.update();

		//Render
		game.render();

		//Draw game

	}
	
	//end of application
	return 0;
}