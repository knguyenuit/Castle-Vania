#include "BrickVertical.h"



CBrickVertical::CBrickVertical()
{
	Init();
}

CBrickVertical::CBrickVertical(Vector2 pos, int m_Width, int m_Height)
{
	Init();
	this->m_Pos = pos;
	this->m_Width = m_Width;
	this->m_Height = m_Height;
}


CBrickVertical::~CBrickVertical()
{

}

Box CBrickVertical::GetBox()
{
	return Box(this->m_Pos.x, this->m_Pos.y, this->m_Width, this->m_Height);
}

void CBrickVertical::Init()
{
	this->m_Id = 712;
	
	m_isLive = true;
}

RECT * CBrickVertical::GetRectRS()
{
	return nullptr;
}

void CBrickVertical::Update(float deltaTime)
{
	OnEnemyCollision(deltaTime, CEnemyManage::GetInstance()->m_ListEnemy);
	OnGroundMovingCollision(deltaTime, CGroundMovingManage::GetInstance()->m_ListGroundMovingPlatform);
}

void CBrickVertical::OnSimonCollision(float deltaTime)
{
}

void CBrickVertical::OnEnemyCollision(float deltaTime, std::vector<CEnemy*> listEnemy)
{
	CDirection normalX;
	CDirection normalY;
	float timeCollision;
	for (std::vector<CEnemy*>::iterator it = listEnemy.begin(); it != listEnemy.end(); it++)
	{
		CEnemy* enemy = *it;
		if (enemy->m_Id == 208)
		{

			timeCollision = COnCollision::GetInstance()->SweepAABB(enemy->GetBox(), this->GetBox(), normalX, normalY, deltaTime);
			if (normalX == ON_LEFT || normalX == ON_RIGHT)
			{
				enemy->isChangeDir = true;
			}
			
		}
	}
}

void CBrickVertical::OnGroundMovingCollision(float deltaTime, std::vector<CGroundMovingPlatform*> listGroundMoving)
{
	CDirection normalX;
	CDirection normalY;
	float timeCollision;
	for (std::vector<CGroundMovingPlatform*>::iterator it = listGroundMoving.begin(); it != listGroundMoving.end(); it++)
	{
		CGroundMovingPlatform* ground = *it;
		/*if (COnCollision::GetInstance()->AABBCheck(ground->GetBox(), this->GetBox()))
		{
			ground->isChangeDir = true;
		}*/
		timeCollision = COnCollision::GetInstance()->SweepAABB(ground->GetBox(), this->GetBox(), normalX, normalY, deltaTime);
		if (normalX == ON_LEFT || normalX == ON_RIGHT)
		{
		ground->isChangeDir = true;
		}
	}

}