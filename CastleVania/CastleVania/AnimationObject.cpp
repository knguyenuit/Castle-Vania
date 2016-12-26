#include "AnimationObject.h"



CAnimationObject::CAnimationObject()
{
}


CAnimationObject::~CAnimationObject()
{
}

void CAnimationObject::Update(float deltaTime)
{
	if (this->m_timeLife >= this->m_timeExist)
	{
		this->m_timeLife = 0.0f;
		this->m_isRemove = true;
	}
	else
	{
		this->ChangeFrame(deltaTime);
		this->m_timeLife += deltaTime;
	}
}

RECT * CAnimationObject::GetRectRS()
{
	return nullptr;
}
