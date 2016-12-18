#include "SmallLight.h"



CSmallLight::CSmallLight()
{
	Init();
}

CSmallLight::CSmallLight(Vector2 pos)
{
	Init();
	this->m_Pos = pos;
}

CSmallLight::CSmallLight(Vector2 pos, ITEM_name enemyItem)
{
	Init();
	this->m_Pos = pos;
	this->enemyItem = enemyItem;
}


void CSmallLight::Init()
{
	this->enemyType = ENEMY_type::SmallLight;
	this->m_Id = this->enemyType;
	this->m_Width = 16;
	this->m_Height = 32;

	this->m_vxDefault = this->m_vx = 0;
	this->m_vyDefault = this->m_vy = 0;
	//Init Animation
	this->m_startFrame = 0;
	this->m_endFrame = 1;
	this->m_currentTime = 0;
	this->m_currentFrame = 0;
	this->m_elapseTimeChangeFrame = 0.15f;
	this->m_increase = 1;
	this->m_totalFrame = 2;
	this->m_column = 2;
}

CSmallLight::~CSmallLight()
{
}

RECT * CSmallLight::GetRectRS()
{
	return UpdateRectResource(this->m_Height, this->m_Width);
}

void CSmallLight::Update(float deltaTime)
{
	ChangeFrame(deltaTime);
}
