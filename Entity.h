#pragma once
#include "common.h"
#include "Components.h"
class Entity
{
	
	std::string		m_tag = "";
	size_t			m_ID = -1;
	bool			m_active = true;

	Entity() {};
	Entity(std::string tag, size_t ID) : m_tag(tag), m_ID(ID) {};

public :
	sptr<CTransform> Transform;
	sptr<CCollision> Collision;
	sptr<CShape>	 Shape;
	sptr<CScore>	 Score;
	sptr<CInput>	 Input;
	sptr<CLifeSpan>	 LifeSpan;

	std::string&	getTag();
	size_t			getID()		const;
	bool			getActive() const;

	void			Destroy();
	void			Activate();
	
	
	friend class EntityManager;
};

