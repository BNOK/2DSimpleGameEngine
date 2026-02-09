#pragma once
#include "Entity.h"


//Entity::Entity(std::string tag, size_t ID) : m_tag(tag), m_ID(ID)
//{
//	Transform = std::make_shared<CTransform>();
//	Collision = std::make_shared<CCollision>();
//	Shape = std::make_shared<CShape>();
//};

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




