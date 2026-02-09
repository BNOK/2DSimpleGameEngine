#pragma once
#include "Entity.h"

typedef std::vector<sptr<Entity>> EntityVec;
typedef std::map<std::string, EntityVec> EntityMap;

class EntityManager
{
	EntityVec m_entities;
	EntityMap m_entityMap;
	EntityVec m_toAdd;

	size_t m_totalEntities;

	void Init(std::string config);

public:

	EntityManager():m_totalEntities(0) {};


	void Update();

	sptr<Entity>& AddEntity(const std::string tag);
	void DestroyDeadEntities();
	const EntityVec& getEntities();
	const EntityVec& getEntities(const std::string tag);

	void ActivateEntities();
};

