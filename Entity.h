#pragma once
#include "common.h"
#include "Components.h"
class Entity
{
	std::string m_tag;
	bool		m_active;
	int			m_ID;

public :
	SPtr<CTransform> Transform;
	SPtr<CCollision> Collision;
	SPtr<CShape>	 Shape;
	SPtr<CScore>	 Score;
	SPtr<CInput>	 Input;
	SPtr<CLifeSpan>	 LifeSpan;
};

