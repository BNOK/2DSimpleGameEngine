#include "Game.h"

void Game::Init(const std::string& path) {
	m_entityManager = std::make_shared<EntityManager>();
	
	bool isloaded = LoadConfig(path);

	
	if(!isloaded)
		return;
}

bool Game::LoadConfig(const std::string& filename)
{
	std::ifstream file(filename);

	if(!file.is_open())
	{
		std::cerr << " file could not be opened !" << std::endl;
		return false;
	}
	
	std::string line;
	while(std::getline(file, line))
	{
		if(line.empty())
			continue;

		std::istringstream iss(line);
		std::string type;
		iss >> type;

		if(type == "Window")
		{
			unsigned int width, height;
			std::string label;
			iss >> width >> height >> label;
			m_window = std::make_unique<sf::RenderWindow>(
				sf::VideoMode({width, height}),
				label);
		}
		// needs to be updated according to config file
		else if(type == "Player" || type == "Enemy" || type == "Bullet")
		{
			std::cout << type << std::endl;
			int properties[11];
			
			for(int i = 0; i < 11; i++)
			{
				float temp;
				iss >> temp;
				properties[i] = temp;
				std::cout << "index :" << i << " value :" << temp << std::endl;
			}
			sptr<Entity>& playerobj = m_entityManager->AddEntity(type);
			playerobj->Shape = std::make_shared<CShape>(
				properties[0],
				static_cast<int>(properties[3]),
				properties[9],
				sf::Color(static_cast<std::uint8_t>(properties[3]), static_cast<std::uint8_t>(properties[4]), static_cast<std::uint8_t>(properties[5])),
				sf::Color(static_cast<std::uint8_t>(properties[6]), static_cast<std::uint8_t>(properties[7]), static_cast<std::uint8_t>(properties[8]))
				);
		}
		
	}
	std::cout << "finished loading config !" << std::endl;
	return true;
}

void Game::sMovement()
{}

void Game::sUserInput()
{}

void Game::sRender()
{
	// clear the window with black color
	m_window->clear(sf::Color::Black);

	auto holder = m_entityManager->getEntities();
	std::cout << holder.size() << std::endl;
	for(int i = 0; i < holder.size(); i++)
	{
		m_window->draw(holder[i]->Shape->shape);
	}

	// end the current frame
	m_window->display();
	
}

void Game::sEnemySpawn()
{}

void Game::sCollision()
{}

void Game::Update()
{
	m_entityManager->Update();




	// last thing is rendering 
	sRender();
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
