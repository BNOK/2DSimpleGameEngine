#pragma once
#include "common.h"
#include "EntityManager.h"

class Game
{
	std::unique_ptr<sf::RenderWindow>	m_window;
	bool								m_paused = false;
	bool								m_isactive = true;
	sptr<EntityManager>					m_entityManager;

	void Init(const std::string& path);
	bool LoadConfig(const std::string& path);

	void sMovement();
	void sUserInput();
	void sRender();
	void sEnemySpawn();
	void sCollision();


public:
	Game();
	Game(std::string path)
	{
		Init(path);
	};

	void Update();


	// getters
	bool GetIsActive();
	bool GetIsPaused();
	
	sf::RenderWindow& GetWindowReference();

	
};

