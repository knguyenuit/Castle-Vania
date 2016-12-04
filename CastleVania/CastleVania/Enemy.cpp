#include "Enemy.h"



CEnemy::CEnemy()
{
}

void CEnemy::InitAnimation()
{
	
}

void CEnemy::Update(float deltaTime)
{
	ChangeFrame(deltaTime);
	//if (CSimon::GetInstance()->GetPos().x >= 300) {
	//	this->m_IsActive = true;
	//}
	//if (this->m_IsActive)
	//{
		this->MoveUpdate(deltaTime);
	//}
	
}

void CEnemy::MoveUpdate(float deltaTime)
{
	if (this->x<CSimon::GetInstance()->m_Pos.x - 300)
	{
		this->m_isRemove = true;
	}
	this->m_Pos.x -= m_vx*deltaTime;
}

RECT * CEnemy::GetRectRS()
{
	return nullptr;
}


CEnemy::~CEnemy()
{
}
