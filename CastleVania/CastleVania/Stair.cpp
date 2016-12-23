#include "Stair.h"



CStair::CStair()
{
	this->Init();
}

CStair::CStair(HideObject_TYPE type, Vector2 pos)
{
	this->Init();
	this->m_typeHideObject = type;
	this->m_Pos = pos;
}



CStair::~CStair()
{
}

void CStair::Init()
{
	this->m_Width = this->m_Height = 32;
	this->simon->isCancelStairMove = true;
}

void CStair::OnSimonCollision(float deltaTime)
{
	if (abs(this->simon->m_Pos.x - this->m_Pos.x) <= 25
		&& abs(this->simon->m_Pos.y - this->m_Pos.y) <= 48)
	{
		this->isSimonCollision = true;
		this->simon->currStairPos = this->m_Pos;
	}
	else
	{
		this->isSimonCollision = false;
	}
}

void CStair::Update(float deltaTime)
{

}

bool CStair::SimonMoveOnStair(float deltaTime)
{
	return false;
}

bool CStair::SimonMoveToStair(float deltaTime)
{
	return false;
}

bool CStair::SimonMoveOutStair(float deltaTime)
{
	return false;
}

void CStair::ResetSimonStair()
{
	this->simon->isArrowKeyDown = this->simon->isArrowKeyUp = false;
	this->simon->isOnStair = false;
	this->simon->isUpStair = this->simon->isDownStair = false;
	this->simon->prepareOnStair = this->simon->prepareOutStair = false;
	this->simon->currSimonStairPos = Vector2(0, 0);
	this->simon->isCancelStairMove = true;
	this->simon->isMoveToStair = this->simon->isFirstStairStep = false;
	this->simon->simon_Status = SIMON_status::IDLE;

}



