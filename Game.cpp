#include "Game.h"

void Game::Init(int width, int height, std::string label) {
	m_window.create(sf::VideoMode({ width,height }), label);

}
