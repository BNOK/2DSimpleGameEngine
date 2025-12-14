#pragma once
#include "EntityManager.h"

void EntityManager::Init(const std::string config) {

}


void EntityManager::Update() {

}

sptr<Entity>& EntityManager::addEntity(const std::string tag) {
	sptr<Entity> result = std::make_shared<Entity>(tag, m_totalEntities);
	m_entities.push_back(result);
	m_entityMap[tag].push_back(result);
	m_totalEntities++;
	return result;
}

void EntityManager::DestroyEntities() {
	static EntityVec toDestroy;
	// removing items from the vector container
	for (auto it = m_entities.begin(); it != m_entities.end();) {
		
		if (!it->get()->m_active) {
			//toDestroy.push_back(*it);
			it = m_entities.erase(it);
		}
		else
		{
			it++;
		}
	}

	// removing the elements from the map container
	for (const auto& pair : m_entityMap) {
		// Get a reference to the specific vector we are working on
		EntityVec currentVector = pair.second;
		// the erase-remove idiom
		currentVector.erase(
			std::remove_if(currentVector.begin(),
				currentVector.end(),
				[](const sptr<Entity> entity) { return entity->m_active; }),
			currentVector.end()
		);
	}
}

const EntityVec& EntityManager::getEntities() {
	return this->m_entities;
}

const EntityVec& EntityManager::getEntities(const std::string tag) {
    return m_entityMap[tag];
}
