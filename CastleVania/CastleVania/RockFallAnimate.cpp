#include "RockFallAnimate.h"



CRockFallAnimate::CRockFallAnimate()
{
}


CRockFallAnimate::CRockFallAnimate(Vector2 pos)
{
	this->m_typeAnimationObject = Animation_object::RockFall;
	this->m_Pos = pos;
	this->Init();
}


CRockFallAnimate::~CRockFallAnimate()
{
}

void CRockFallAnimate::Init()
{
	this->m_Dir = LEFT;
	this->m_timeExist = 0.4f;
	this->m_Width = 80;
	this->m_Height = 80;
	//init animation
	this->m_elapseTimeChangeFrame = 0.1f;
	this->m_startFrame = 0;
	this->m_endFrame = 0;
	this->m_currentTime = 0;
	this->m_currentFrame = 0;
	this->m_increase = 1;
	this->m_totalFrame = 4;
	this->m_column = 4;
}

RECT * CRockFallAnimate::GetRectRS()
{
	return this->UpdateRectResource(this->m_Height, this->m_Width);
}

Box CRockFallAnimate::GetBox()
{
	return Box(this->m_Pos.x + 38, this->m_Pos.y - 40, this->m_Width, this->m_Height);
}

void CRockFallAnimate::Update(float deltaTime)
{
	if (this->isCaneCollision == false)
	{
		this->OnCaneCollision(deltaTime);
	}
	this->OnSimonCollision(deltaTime);
	if (this->isCaneCollision == true)
	{
		this->m_startFrame = 1;
		this->m_endFrame = 3;
		this->ChangeFrame(deltaTime);
		if (this->m_timeLife == 0)
		{
			ManageAudio::GetInstance()->playSound(TypeAudio::Hit);
		}
		if (this->m_timeLife >= this->m_timeExist)
		{
			if (this->itemName != ITEM_name::None)
			{
				CItemManage::GetInstance()->CreateItem(this->itemName, this->m_Pos);
			}
			this->m_isRemove = true;
			this->m_timeLife = 0.0f;
			this->isCaneCollision = false;
		}
		else
		{
			this->m_timeLife += deltaTime;
		}
	}
}

void CRockFallAnimate::OnCaneCollision(float deltaTime)
{
	if (CCollision::GetInstance()->AABBCheck(this->simon->cane->GetBox(), this->GetBox()))
	{
		this->isCaneCollision = true;
	}
	
}

void CRockFallAnimate::OnSimonCollision(float deltaTime)
{
	CDirection normalX;
	CDirection normalY;
	float timeCollision;
	timeCollision = COnCollision::GetInstance()->SweepAABB(this->simon->GetBox(), this->GetBox(), normalX, normalY, deltaTime);
	if (normalX == CDirection::ON_RIGHT)
	{
		if (this->simon->m_Dir == Direction::LEFT)
		{
			this->simon->m_vx = -this->simon->m_vxDefault;
		}
		else
		{
			this->simon->m_vx = 0;
		}
	}
}
