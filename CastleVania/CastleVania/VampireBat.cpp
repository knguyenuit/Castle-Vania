#include "VampireBat.h"

CVampireBat::CVampireBat()
{
	Init();
}

CVampireBat::CVampireBat(Vector2 pos)
{
	Init();
	this->SetPos(pos);
}


void CVampireBat::Init()
{
	this->enemyType = ENEMY_type::VampireBat;
	this->m_Id = this->enemyType;
	this->m_Width = 32;
	this->m_Height = 32;

	this->m_vx = 50;

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
	if (this->x<CSimon::GetInstance()->m_Pos.x - 300)
	{
		this->m_isRemove = true;
	}
	this->m_Pos.x -= m_vx*deltaTime;
}

CVampireBat::~CVampireBat()
{
}
