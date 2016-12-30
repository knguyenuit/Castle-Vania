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
	posIntanceFireBall1 = Vector2(this->m_Pos.x, this->m_Pos.y);
	posIntanceFireBall2 = Vector2(this->m_Pos.x, this->m_Pos.y + 20);
}

void CDragonSkullCannon::Update(float deltaTime)
{
	timeCountIntanceFireBall += deltaTime;
	if (timeCountIntanceFireBall >= 1)
	{
		posIntanceFireBall1 = Vector2(this->m_Pos.x, this->m_Pos.y);
		posIntanceFireBall2 = Vector2(this->m_Pos.x, this->m_Pos.y - 50);
		CFireBallManage::GetInstance()->CreateFireBall(posIntanceFireBall1, RIGHT);
		CFireBallManage::GetInstance()->CreateFireBall(posIntanceFireBall2, LEFT);
		timeCountIntanceFireBall = 0;
	}
	CFireBallManage::GetInstance()->Update(deltaTime);
	if (CSimon::GetInstance()->cane->m_checkActive)
	{
		OnCaneCollision();
	}
	CFireBallManage::GetInstance()->Draw();
	OnWeaponCollision(deltaTime, CWeaponManage::GetInstance()->m_weaponList);
}
