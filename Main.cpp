#include <iostream>
#include "Game.h"

//sf::Clock clock;
//float deltaTime;

int main()
{
	//calculate delta time
	//deltaTime = clock.restart().asSeconds();

	//Init srand
	std::srand(static_cast<unsigned>(time(NULL)));

	//Init game engine
	Game game;

	//Initializing and playing soundtrack before while loop, since only initiated once and not repeated each frame.
	sf::Music music;
	music.openFromFile("Intergalactic Odyssey.ogg");
	music.setPitch(0.5);
	music.setVolume(40);
	music.play();
	music.setLoop(true);

	while (game.running() && !game.getEndGame())
	{
		//Update
		game.update();

		//Render
		game.render();

		//Draw game

	}

	//Show end screen


	
	//end of application/title screen
	return 0;
}