#pragma once
#include "EntityManager.h"

void EntityManager::Init(const std::string config) {

}


void EntityManager::Update() {
	//adding entities from the to add vector and map
	for(int i = 0; i < m_toAdd.size(); i++)
	{
		m_entities.push_back(m_toAdd[i]);
		std::string temptag = m_toAdd[i]->getTag();
		m_entityMap[temptag].push_back(m_toAdd[i]);
	}

	m_toAdd.clear();
	// delete dead entities
	DestroyDeadEntities();
}

sptr<Entity>& EntityManager::AddEntity(const std::string tag) {

	sptr<Entity> entity = std::shared_ptr<Entity>(new Entity(tag, m_totalEntities));
	m_toAdd.push_back(entity);
	m_totalEntities++;
	return entity;
}

void EntityManager::ActivateEntities() {

	for (auto& entity : m_toAdd) {
		m_entities.push_back(entity);
		m_entityMap[entity->m_tag].push_back(entity);
	}
}

void EntityManager::DestroyDeadEntities() {
	
	// removing from entities vector
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

	// removing the elements from the entities map
	for (const auto& pair : m_entityMap) {
		// Get a reference to the specific vector we are working on
		EntityVec currentVector = pair.second;
		// the erase-remove idiom
		currentVector.erase(
			std::remove_if(currentVector.begin(),
				currentVector.end(),
				[](const sptr<Entity> entity) { return entity->getActive(); }),
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
