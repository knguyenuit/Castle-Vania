#include "ChangeDown.h"



CChangeDown::CChangeDown()
{
}

CChangeDown::CChangeDown(HideObject_TYPE type, Vector2 pos)
{
	this->m_Width = 32;
	this->m_Height = 32;
	this->m_typeHideObject = type;
	this->m_Pos = pos;
}


CChangeDown::~CChangeDown()
{
}

void CChangeDown::Update(float deltaTime)
{
	
	OnSimonCollision(deltaTime);
}

void CChangeDown::OnSimonCollision(float deltaTime)
{
	CDirection normalX;
	CDirection normalY;
	float timeCollision;
	timeCollision = COnCollision::GetInstance()->SweepAABB(this->simon->GetBox(), this->GetBox(), normalX, normalY, deltaTime);
	if (normalX == CDirection::ON_LEFT || normalX == CDirection::ON_RIGHT)
	{
		CSimon::GetInstance()->canChangeDown = true;
	}
	
}
