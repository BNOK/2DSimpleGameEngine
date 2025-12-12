#include "Game.h"

/* Variable declaration notation :
   m_varName : private variables
   varName   : public variables */

int main()
{
    Game mainGame;

    float radius = 5.0f;
    // The main loop - ends as soon as the window is closed
    while (mainGame.m_window.isOpen())
    {
        // Event processing
        while (const std::optional event = mainGame.m_window.pollEvent())
        {
            // Request for closing the window
            if (event->is<sf::Event::Closed>())
                mainGame.m_window.close();
        }

        radius += 0.1f;


        // Clear the whole window before rendering a new frame
        mainGame.m_window.clear();

        // Draw some graphical entities
        mainGame.m_window.draw(sf::CircleShape(radius));

        // End the current frame and display its contents on screen
        mainGame.m_window.display();
    }
}