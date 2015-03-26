#define _CRTDBG_MAP_ALLOC
#ifdef _DEBUG
	#ifndef DBG_NEW
		#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
		#define new DBG_NEW
	#endif
#endif  // _DEBUG

//#include <stdlib.h>
//#include <crtdbg.h>

#include <SFML/Graphics.hpp>
#include <SFML\Window.hpp>
#include "Game.h"

using namespace std;

int main()
{
	//_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	
	Game game;
    sf::RenderWindow window(sf::VideoMode(800, 800), "");

	//window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(false);
	window.setKeyRepeatEnabled(false);

	sf::Clock gameTime;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
			{
				_CrtDumpMemoryLeaks();
				window.close();
			}
		}
		////////////// Updating ///////////////

		sf::Time gameLapse = gameTime.restart();

		game.update(gameLapse, window, event);
		

		////////////// Updating ///////////////


		////////////// Drawing ///////////////
		window.clear(sf::Color::White);

		game.draw(window);

        window.display();

		////////////// Drawing ///////////////
    }
    return 0;
}