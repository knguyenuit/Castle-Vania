#include "Enemy.h"
#include "Simon.h"

CEnemy::CEnemy()
{
	CEnemy::Init();
}

void CEnemy::Init()
{
	this->m_State = ENEMY_state::IDLE;
	this->m_isRemove = false;
	this->m_vx = 100;
	this->m_vy = 200;
	this->m_Dir = Direction::LEFT;
}

void CEnemy::InitAnimation()
{
	
}

void CEnemy::Update(float deltaTime)
{
	this->ChangeFrame(deltaTime);
	if (this->m_Pos.x < CCamera::GetInstance()->m_pos.x+600)
	{
		switch (this->enemyType)
		{
		case BlackLeopard:
			this->m_State = ENEMY_state::JUMP;
			break;
		default:
			this->m_State = ENEMY_state::MOVE;
			break;
		}
		
		if (CCamera::GetInstance()->m_pos.x>this->m_Pos.x)
		{
			this->m_isRemove = true;
		}
	}
	if (this->m_State != ENEMY_state::IDLE)
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
	
	switch (this->m_State)
	{
	case ENEMY_state::MOVE:
		this->m_Pos.x -= m_vx*deltaTime;
		break;
	case ENEMY_state::FREE:
		this->m_Pos.y -= m_vy*deltaTime;
		break;
	default:
		break;
	}
	
}
void CEnemy::changeState(ENEMY_state state)
{
	this->m_State = state;
}
RECT * CEnemy::GetRectRS()
{
	return nullptr;
}


CEnemy::~CEnemy()
{
}
