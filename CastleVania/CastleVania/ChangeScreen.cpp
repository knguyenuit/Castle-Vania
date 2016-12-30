#include "ChangeScreen.h"



CChangeScreen::CChangeScreen()
{
	this->m_Width = 32;
	this->m_Height = 96;
}

CChangeScreen::CChangeScreen(HideObject_TYPE type, Vector2 pos)
{
	this->m_Width = 32;
	this->m_Height = 96;
	this->m_typeHideObject = type;
	this->m_Pos = pos;
}


CChangeScreen::~CChangeScreen()
{
}

void CChangeScreen::Update(float deltaTime)
{
	OnSimonCollision(deltaTime);
}

void CChangeScreen::OnSimonCollision(float deltaTime)
{
	CDirection normalX;
	CDirection normalY;
	float timeCollision;
	timeCollision = COnCollision::GetInstance()->SweepAABB(this->simon->GetBox(), this->GetBox(), normalX, normalY, deltaTime);
	/*if (normalX == CDirection::ON_LEFT || normalX == CDirection::ON_RIGHT || normalY == ON_UP || normalY == ON_DOWN)
	{
		
		this->simon->isCheckChangeState = true;
		ManageAudio::GetInstance()->playSound(TypeAudio::Open_Door);
	}*/
	if (COnCollision::GetInstance()->AABBCheck(this->simon->GetBox(), this->GetBox()))
	{
		this->simon->isCheckChangeState = true;
		ManageAudio::GetInstance()->playSound(TypeAudio::Open_Door);
	}
}
