#include "Brick.h"



CBrick::CBrick()
{
	Init();
}

CBrick::CBrick(Vector2 pos)
{
	Init();
	this->m_Pos = pos;
}


CBrick::~CBrick()
{
}

Box CBrick::GetBox()
{
	if (!simon->isSit)
	{
		return Box(this->m_Pos.x, this->m_Pos.y, this->m_Width, this->m_Height);
	}
	else
	{
		return Box(this->m_Pos.x, this->m_Pos.y, this->m_Width, this->m_Height + 10);
	}
}

void CBrick::Init()
{
	this->m_Id = 702;
	this->m_Width = 32;
	this->m_Height = 32;
	m_isLive = true;
}

RECT * CBrick::GetRectRS()
{
	RECT * rec = new RECT();
	rec->left = 0;
	rec->right = rec->left + m_Width;
	rec->top = 0;
	rec->bottom = rec->top + m_Height;
	return rec;
}

void CBrick::Update(float deltaTime)
{
	this->OnSimonCollision(deltaTime);
	OnItemCollision(deltaTime, CItemManage::GetInstance()->m_ListItem);
	OnEnemyCollision(deltaTime, CEnemyManage::GetInstance()->m_ListEnemy);
}

void CBrick::OnSimonCollision(float deltaTime)
{
	if (this->simon->simon_Status != SIMON_status::ONSTAIR)
	{
		CDirection normalX;
		CDirection normalY;
		float timeCollision;
		timeCollision = COnCollision::GetInstance()->SweepAABB(this->simon->GetBox(), this->GetBox(), normalX, normalY, deltaTime);
		if (normalY == CDirection::ON_DOWN && this->simon->isOnStair == false && this->simon->isMoveToStair == false)
		{
			simon->m_Pos.y = this->m_Pos.y + this->m_Height / 2 + simon->m_Height / 2 - 8;
			this->simon->simon_Status = SIMON_status::IDLE;
			this->simon->isKey_X = false;
			/*this->simon->isMoveJump = false;*/
		}
		if (this->simon->isMoveToStair == false && this->simon->isOnStair == false && this->simon->isDownStair == false && this->simon->prepareOnStair == false)
		{
			if (COnCollision::GetInstance()->AABBCheck(this->simon->GetBox(), this->GetBox()))
			{

				if (this->simon->isSit == true && (this->simon->m_currentFrame == 4 || this->simon->m_currentFrame == 15 || this->simon->m_currentFrame == 16 || this->simon->m_currentFrame == 17))
				{
					simon->m_Pos.y = this->m_Pos.y + this->m_Height / 2 + simon->m_Height / 2 - 24;
				}
				else
				{
					simon->m_Pos.y = this->m_Pos.y + this->m_Height / 2 + simon->m_Height / 2 - 8;
				}
			}
		}
	}
}

void CBrick::OnItemCollision(float deltaTime, std::vector<CItem*> listItem)
{
	CDirection normalX;
	CDirection normalY;
	float timeCollision;
	for (std::vector<CItem*>::iterator it = listItem.begin(); it != listItem.end(); it++)
	{
		CItem* item = *it;
		timeCollision = COnCollision::GetInstance()->SweepAABB(item->GetBox(), this->GetBox(), normalX, normalY, deltaTime);
		if (normalY == ON_DOWN)
		{
			item->m_vyDefault = 0;
		}
	}
}

void CBrick::OnEnemyCollision(float deltaTime, std::vector<CEnemy*> listEnemy)
{
	CDirection normalX;
	CDirection normalY;
	float timeCollision;
	for (std::vector<CEnemy*>::iterator it = listEnemy.begin(); it != listEnemy.end(); it++)
	{
		CEnemy* enemy = *it;
		timeCollision = COnCollision::GetInstance()->SweepAABB(enemy->GetBox(), this->GetBox(), normalX, normalY, deltaTime);
		if (normalY == ON_DOWN)
		{
			if (enemy->m_Id == 202)
			{
				int a = 5;
			}
		}
	}
}
