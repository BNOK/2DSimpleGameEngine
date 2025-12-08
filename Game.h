#pragma once
#include "common.h"
#include "EntityManager.h"

class Game
{
	sf::RenderWindow	m_window;
	bool				m_paused = false;
	bool				m_isactive = true;
	Entity				m_player;
	EntityManager		m_entityManager;

	void Init(int width, int height, std::string label);
	void sMovement();
	void sUserInput();
	void sRender();
	void sEnemySpawn();
	void sCollision();

public:
	Game(int width, int height, std::string label) {
		Init(width, height, label);
	}
	void Update();
};

