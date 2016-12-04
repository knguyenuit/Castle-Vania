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


CBlackLeopard::~CBlackLeopard()
{
}

void CBlackLeopard::Init()
{
	this->enemyType = ENEMY_type::BlackLeopard;
	this->m_Id = this->enemyType;
	this->m_Width = 64;
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

void CBlackLeopard::MoveUpdate(float deltaTime)
{
}
