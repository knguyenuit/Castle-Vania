
#include "BlackLeopard.h"
CBlackLeopard::CBlackLeopard()
{
	Init();
}

CBlackLeopard::CBlackLeopard(Vector2 pos)
{
	Init();
	this->SetPos(pos);
}

void CBlackLeopard::Init()
{
		this->enemyType = ENEMY_type::BlackLeopard;
		this->m_Id = this->enemyType;
		this->m_Width = 64;
		this->m_Height = 32;

		this->m_vx = 200;
		this->m_vy = 200;
		//init animation
		this->m_startFrame = 0;
		this->m_endFrame = 0;
		this->m_currentTime = 0;
		this->m_currentFrame = 0;
		this->m_elapseTimeChangeFrame = 0.15f;
		this->m_increase = 0;
		this->m_totalFrame = 4;
		this->m_column = 4;
	
}

void CBlackLeopard::MoveUpdate(float deltaTime)
{
	switch (this->m_State)
	{
	case ENEMY_state::IDLE:
		this->m_startFrame = 0;
		this->m_endFrame = 0;
		this->m_increase = 0;
		break;
	case ENEMY_state::JUMP:
		this->m_startFrame = 3;
		this->m_endFrame = 3;
		this->m_increase = 0;
		if (this->m_Pos.y>48)
		{
			this->m_Pos.x -= this->m_vx*deltaTime;
			this->m_Pos.y -= this->m_vy*deltaTime;
		} else 
		{
			this->changeState(ENEMY_state::MOVE);
		}
		break;
	case ENEMY_state::FREE:
		this->m_startFrame = 3;
		this->m_endFrame = 3;
		this->m_increase = 0;
		this->m_Pos.y -= m_vy*deltaTime;
	case ENEMY_state::MOVE:
		this->m_startFrame = 1;
		this->m_endFrame = 2;
		this->m_increase = 1;
		this->m_Pos.x -= m_vx*deltaTime;
	default:
		break;
	}
}

RECT * CBlackLeopard::GetRectRS()
{
	return this->UpdateRectResource(m_Height, m_Width);
}


CBlackLeopard::~CBlackLeopard()
{
}
