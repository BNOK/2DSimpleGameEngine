#pragma once
#include "Entity.h"

typedef std::vector<sptr<Entity>> EntityVec;
typedef std::map<std::string, EntityVec> EntityMap;

class EntityManager
{
	EntityVec m_entities;
	EntityMap m_entityMap;
	EntityVec m_toAdd;
	EntityVec m_toDestroy;

	void Init();

public:
	void Update();

	std::vector<Entity>& getEntities();
	std::vector<Entity>& getEntities(std::string tag);
};

