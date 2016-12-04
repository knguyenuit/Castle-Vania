#include "Zombie.h"



CZombie::CZombie()
{
	Init();
}

CZombie::CZombie(Vector2 pos)
{
	Init();
	this->SetPos(pos);
}
void CZombie::Init() {
	this->enemyType = ENEMY_type::Zombie;
	this->m_Id = this->enemyType;
	this->m_Width = 34;
	this->m_Height = 64;
	
	this->m_vx = 50;

	//init animation
	this->m_startFrame = 0;
	this->m_endFrame = 1;
	this->m_currentTime = 0;
	this->m_currentFrame = 0;
	this->m_elapseTimeChangeFrame = 0.15f;
	this->m_increase = 1;
	this->m_totalFrame = 2;
	this->m_column = 2;
}



CZombie::~CZombie()
{
}
void CZombie::MoveUpdate(float deltaTime)
{

}

//RECT * CZombie::GetRectRS()
//{
//	return this->UpdateRectResource(this->m_Height,this->m_Width);
//}
