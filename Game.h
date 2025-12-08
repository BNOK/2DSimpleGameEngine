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

	void init();
	void sMovement();
	void sUserInput();
	void sRender();
	void sEnemySpawn();
	void sCollision();

public:

	void Update();

};

