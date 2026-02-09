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
			m_window->setFramerateLimit(60);
		}
		// needs to be updated according to config file
		else if(type == "Player" || type == "Enemy" || type == "Bullet")
		{
			std::cout << type << std::endl;
			float properties[11];
			
			for(int i = 0; i < 11; i++)
			{
				float temp;
				iss >> temp;
				properties[i] = temp;
				//std::cout << "index :" << i << " value :" << temp << std::endl;
			}
			auto gameobject = m_entityManager->AddEntity(type);
			if(!gameobject)
			{
				continue;
			}
			gameobject->Shape = std::make_shared<CShape>(
				properties[0],
				properties[10],
				properties[9],
				sf::Color(properties[3], properties[4], properties[5]),
				sf::Color(properties[6], properties[7], properties[8])
				);

			//gameobject->Collision = std::make_shared<CCollision>(properties[1]);
			Vec2 startposition(m_window->getSize().x /2, m_window->getSize().y /2);
			Vec2 scale(properties[0],properties[0]);
			Vec2 speed(properties[2], properties[2]);
			gameobject->Transform = std::make_shared<CTransform>(startposition, scale, speed, 0.0f);


			std::cout << "created object of type : " << type << std::endl;

		}
		
	}
	std::cout << "finished loading config !" << std::endl;
	return true;
}

void Game::Update()
{
	
	m_entityManager->Update();
	

	
	sMovement();

	// last thing is rendering 
	sRender();
}

void Game::sMovement()
{
	auto array = m_entityManager->getEntities();
	for(int i = 0; i < array.size(); i++)
	{
		//std::cout << "current object : " << array[i]->getTag() << std::endl;
		std::cout << "current position" << array[i]->Transform->Position.x  << "||" << array[i]->Transform->Position.y << std::endl;
		auto& transform = array[i]->Transform;
		transform->Position = transform->Position + transform->Speed;
		array[i]->Shape->shape.setPosition(sf::Vector2f(transform->Position.x, transform->Position.y));
	}
}

void Game::sUserInput()
{
	

}

void Game::sRender()
{
	// clear the window with black color
	m_window->clear(sf::Color::Black);

	auto holder = m_entityManager->getEntities();
	//std::cout << holder.size() << std::endl;
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
