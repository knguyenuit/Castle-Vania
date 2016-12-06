#include "VampireBat.h"

CVampireBat::CVampireBat()
{
	Init();
}

CVampireBat::CVampireBat(Vector2 pos)
{
	Init();
	this->SetPos(pos);
	this->m_PosDefault.x = pos.x;
	this->m_PosDefault.y = pos.y;
}


void CVampireBat::Init()
{
	this->enemyType = ENEMY_type::VampireBat;
	this->m_Id = this->enemyType;
	this->m_Width = 32;
	this->m_Height = 32;

	this->m_vx = 200;

	//init animation
	this->m_startFrame = 0;
	this->m_endFrame = 3;
	this->m_currentTime = 0;
	this->m_currentFrame = 0;
	this->m_elapseTimeChangeFrame = 0.15f;
	this->m_increase = 1;
	this->m_totalFrame = 4;
	this->m_column = 4;
}

RECT * CVampireBat::GetRectRS()
{
	return this->UpdateRectResource(m_Height, m_Width);
}

void CVampireBat::MoveUpdate(float deltaTime)
{
	switch (this->m_State)
	{
	case ENEMY_state::MOVE:
		if (this->m_Dir==LEFT)
		{
			this->m_Pos.x -= this->m_vx*deltaTime;
		} 
		else 
		{
			this->m_Pos.x += this->m_vx*deltaTime;
		}
		this->m_Pos.y = this->m_PosDefault.y + std::sin((this->m_Pos.x-this->m_PosDefault.x)/200*PI) * 30;
		break;
	default:
		break;
	}
}

CVampireBat::~CVampireBat()
{
}
