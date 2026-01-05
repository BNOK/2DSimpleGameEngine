#include "Game.h"

void Game::Init(uint16_t width, uint16_t height, std::string label) {
	
	m_window = std::make_unique<sf::RenderWindow>(
		sf::VideoMode({width, height}),
		label
	);

}

bool Game::GetIsActive()
{
	return m_isactive;
}

bool Game::GetIsPaused()
{
	return m_paused;
}

sf::RenderWindow& Game::GetWindowReference()
{
	return *m_window;
}
