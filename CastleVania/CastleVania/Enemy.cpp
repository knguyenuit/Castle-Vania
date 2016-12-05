#include "Enemy.h"
#include "Simon.h"
CEnemy::CEnemy()
{
	this->m_IsActive = false;
	this->m_isRemove = false;
	this->m_IsAlive = true;
	this->m_vx = 100;
	this->m_Dir = Direction::LEFT;
}

void CEnemy::InitAnimation()
{
	
}

void CEnemy::Update(float deltaTime)
{
	ChangeFrame(deltaTime);
	if (this->m_Pos.x-200 <= CSimon::GetInstance()->GetPos().x)
	{
		this->m_IsActive = true;
		if (CCamera::GetInstance()->m_pos.x>this->m_Pos.x)
		{
			this->m_isRemove = true;
		}
	}
	if (this->m_IsActive)
	{
		this->MoveUpdate(deltaTime);
	}
	
}

void CEnemy::MoveUpdate(float deltaTime)
{
	//if (this->m_Pos.x <= CSimon::GetInstance()->GetPos().x)
	//{
	//	this->m_IsActive = false;
	//	MessageBox(NULL, "A", "b", true);
	//}
	this->m_Pos.x -= m_vx*deltaTime;
}

RECT * CEnemy::GetRectRS()
{
	return nullptr;
}


CEnemy::~CEnemy()
{
}
