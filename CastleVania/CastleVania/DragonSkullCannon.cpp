#include "DragonSkullCannon.h"



CDragonSkullCannon::CDragonSkullCannon()
{
}

CDragonSkullCannon::CDragonSkullCannon(Vector2 pos)
{
	Init();
	this->m_Pos = pos;
}


CDragonSkullCannon::~CDragonSkullCannon()
{
}

void CDragonSkullCannon::Init()
{
	this->enemyType = ENEMY_type::DragonSkullCanon;
	this->m_Id = this->enemyType;
	this->m_State = ENEMY_state::IDLE;
	this->m_Dir = LEFT;
	this->m_Width = 32;
	this->m_Height = 64;
	this->m_vx = 0;
	this->m_vy = 0;
}

void CDragonSkullCannon::Update(float deltaTime)
{
	timeCountIntanceFireBall += deltaTime;
	if (timeCountIntanceFireBall >= 1)
	{
		CFireBallManage::GetInstance()->CreateFireBall(this -> m_Pos, this->m_Dir);
		timeCountIntanceFireBall = 0;
	}
	CFireBallManage::GetInstance()->Update(deltaTime);
}
