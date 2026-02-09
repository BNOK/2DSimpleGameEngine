#include "Game.h"

/* Variable declaration notation :
   m_varName : private variables
   varName   : public variables */

int main()
{
    std::string configPath = "D:\\Projects\\2DSimpleGameEngine\\Config.txt";
    Game mainGame(configPath);
    sf::RenderWindow& window = mainGame.GetWindowReference();

	while(mainGame.GetWindowReference().isOpen())
	{
        // check all the window's events that were triggered since the last iteration of the loop
        while(const std::optional event = window.pollEvent())
        {
            // "close requested" event: we close the window
            if(event->is<sf::Event::Closed>())
                window.close();
        }


        mainGame.Update();
	}
}