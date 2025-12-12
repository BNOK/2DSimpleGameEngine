#pragma once
#include "common.h"
#include "Components.h"
class Entity
{
	std::string		m_tag = "";
	size_t			m_ID;
	bool			m_active = false;

	Entity() {};
	Entity(std::string tag, size_t ID, bool isactive) : m_tag(tag), m_ID(ID), m_active(isactive) {};

public :
	sptr<CTransform> Transform;
	sptr<CCollision> Collision;
	sptr<CShape>	 Shape;
	sptr<CScore>	 Score;
	sptr<CInput>	 Input;
	sptr<CLifeSpan>	 LifeSpan;

	std::string& getTag();
	size_t	getID() const;
	void	Destroy();
	void	Activate();

	friend class EntityManager;
	
};

