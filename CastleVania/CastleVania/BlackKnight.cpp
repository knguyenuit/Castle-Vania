#include "BlackKnight.h"



CBlackKnight::CBlackKnight()
{
	Init();
}

CBlackKnight::CBlackKnight(Vector2 pos)
{
	Init();
	this->SetPos(pos);
}


CBlackKnight::~CBlackKnight()
{
	delete this;
}

void CBlackKnight::Init()
{
	this->enemyType = ENEMY_type::BlackKnight;
	this->m_Id = this->enemyType;
	this->m_Width = 32;
	this->m_Height = 64;

	this->m_vx = 100;

	//init animation
	this->m_startFrame = 0;
	this->m_endFrame = 3;
	this->m_currentTime = 0;
	this->m_currentFrame = 0;
	this->m_elapseTimeChangeFrame = 0.15f;
	this->m_increase = 1;
	this->m_totalFrame = 4;
	this->m_column = 4;
	this->m_Dir = Direction::LEFT;
}

RECT * CBlackKnight::GetRectRS()
{
	return this->UpdateRectResource(m_Height, m_Width);
}
