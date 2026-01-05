#pragma once
#include "common.h"
#include "EntityManager.h"

class Game
{
	std::unique_ptr<sf::RenderWindow> m_window;
	bool				m_paused = false;
	bool				m_isactive = true;
	EntityManager*	m_entityManager;

	void Init(uint16_t width, uint16_t height, std::string label);
	void sMovement();
	void sUserInput();
	void sRender();
	void sEnemySpawn();
	void sCollision();

public:
	Game();
	Game(uint16_t width, uint16_t height, std::string label)
	{
		Init(width, height, label);
	};
	void Update();


	// getters
	bool GetIsActive();
	bool GetIsPaused();
	
	sf::RenderWindow& GetWindowReference();

	
};

