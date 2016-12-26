#include "FireOnAnimate.h"



CFireOnAnimate::CFireOnAnimate()
{
	this->m_typeAnimationObject = Animation_object::FireOn;
}

CFireOnAnimate::CFireOnAnimate(Vector2 pos)
{
	this->m_typeAnimationObject = Animation_object::FireOn;
	this->m_Pos = this->m_PosDefault = pos;
	this->Init();
}


CFireOnAnimate::~CFireOnAnimate()
{
}

void CFireOnAnimate::Init()
{
	this->m_Width = 60;
	this->m_Height = 44;
	//init animation
	this->m_elapseTimeChangeFrame = 0.1f;
	this->m_startFrame = 0;
	this->m_endFrame = 2;
	this->m_currentTime = 0;
	this->m_currentFrame = 0;
	this->m_increase = 1;
	this->m_totalFrame = 3;
	this->m_column = 3;
}

RECT * CFireOnAnimate::GetRectRS()
{
	return this->UpdateRectResource(this->m_Height, this->m_Width);
}
