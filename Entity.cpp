#pragma once
#include "Entity.h"


std::string& Entity::getTag() {
	return this->m_tag;
}

size_t Entity::getID() const
{
	return this->m_ID;
}

bool Entity::getActive() const{
	return m_active;
}

void Entity::Destroy()
{
	m_active = false;
}

void Entity::Activate()
{
	m_active = true;
}




