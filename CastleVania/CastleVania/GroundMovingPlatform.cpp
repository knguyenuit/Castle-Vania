#include "GroundMovingPlatform.h"



CGroundMovingPlatform::CGroundMovingPlatform()
{
	Init();
}

CGroundMovingPlatform::CGroundMovingPlatform(Vector2 pos)
{
	Init();
	this->m_Pos = pos;
}


CGroundMovingPlatform::~CGroundMovingPlatform()
{
}

void CGroundMovingPlatform::Init()
{
	this->m_Id = 653;
	this->m_Width = 64;
	this->m_Height = 16;

	this->m_vx = 20;
	this->m_vy = 0;
	this->m_Dir = LEFT;
}

void CGroundMovingPlatform::Update(float deltaTime)
{
	//this->m_Pos.x += this->m_vx * deltaTime;
	MoveUpdate(deltaTime);
	OnSimonCollision(deltaTime);
}

void CGroundMovingPlatform::MoveUpdate(float deltaTime)
{
	
		if (isChangeDir)
		{
			if (m_Dir == Direction::LEFT)
			{
				m_Dir = Direction::RIGHT;
				isChangeDir = false;
			}
			else
			{
				m_Dir = Direction::LEFT;
				isChangeDir = false;
			}
		}
		if (this->m_Dir == LEFT)
		{
			this->m_Pos.x -= this->m_vx * deltaTime;
			distanceX += this->m_vx * deltaTime;
		}
		else
		{
			this->m_Pos.x += this->m_vx * deltaTime;
			distanceX += this->m_vx * deltaTime;
		}
		if (distanceX > 32)
		{
			float a = distanceX;
			isChangeDir = true;
			distanceX = 0;
		}
		
}


Box CGroundMovingPlatform::GetBox()
{
		return Box(this->m_Pos.x, this->m_Pos.y, this->m_Width, this->m_Height, this->m_vx, this->m_vy);	
}

void CGroundMovingPlatform::OnSimonCollision(float deltaTime)
{
	if (this->simon->simon_Status != SIMON_status::ONSTAIR)
	{
		CDirection normalX;
		CDirection normalY;
		float timeCollision;
		timeCollision = COnCollision::GetInstance()->SweepAABB(this->simon->GetBox(), this->GetBox(), normalX, normalY, deltaTime);
		if (normalY == CDirection::ON_DOWN && this->simon->isOnStair == false && this->simon->isMoveToStair == false && this->simon->isCollisionEnemy == false)
		{
			simon->m_Pos.y = this->m_Pos.y + this->m_Height / 2 + simon->m_Height / 2 - 8;
			this->simon->simon_Status = SIMON_status::IDLE;
			this->simon->isKey_X = false;
			
			/*this->simon->isMoveJump = false;*/
		}
		if ((normalX == CDirection::ON_LEFT || normalX == CDirection::ON_RIGHT) && this->simon->isMoveJump == true)
		{
			this->simon->m_vx = 0;
		}
		if (this->simon->isCollisionEnemy == false)
		{
			if (this->simon->isMoveToStair == false && this->simon->isOnStair == false && this->simon->isDownStair == false && this->simon->prepareOnStair == false && this->simon->isJump == false)
			{
				if (this->simon->m_Pos.y > this->m_Pos.y)
				{
					if (COnCollision::GetInstance()->AABBCheck(this->simon->GetBox(), this->GetBox()))
					{
						if (this->m_Dir == LEFT)
						{
							this->simon->m_Pos.x -= this->m_vx * deltaTime;
						}
						else
						{
							this->simon->m_Pos.x += this->m_vx * deltaTime;
						}
						if (this->simon->isSit == true && (this->simon->m_currentFrame == 4 || this->simon->m_currentFrame == 15 || this->simon->m_currentFrame == 16 || this->simon->m_currentFrame == 17))
						{
							simon->m_Pos.y = this->m_Pos.y + this->m_Height / 2 + simon->m_Height / 2 - 26;
						}
						else
						{
							simon->m_Pos.y = this->m_Pos.y + this->m_Height / 2 + simon->m_Height / 2 - 12;
						}
					}
				}

			}
		}

	}
	/*if (COnCollision::GetInstance()->AABBCheck(this->GetBox, simon->GetBox()))
	{
		if (this->simon->m_Dir == LEFT)
		{
			this->simon->m_Pos.x -= this -> m_vx * deltaTime;
		}
		else
		{
			this->simon->m_Pos.x += this->m_vx * deltaTime;
		}
	}*/
}


