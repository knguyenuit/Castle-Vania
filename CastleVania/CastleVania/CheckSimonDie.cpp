#include "CheckSimonDie.h"



CCheckSimonDie::CCheckSimonDie()
{
}

CCheckSimonDie::CCheckSimonDie(HideObject_TYPE type, Vector2 pos)
{
	this->m_Width = 32;
	this->m_Height = 32;
	this->m_typeHideObject = type;
	this->m_Pos = pos;
}


CCheckSimonDie::~CCheckSimonDie()
{
}

void CCheckSimonDie::Update(float deltaTime)
{
	OnSimonCollision(deltaTime);
}

void CCheckSimonDie::OnSimonCollision(float deltaTime)
{
	CDirection normalX;
	CDirection normalY;
	float timeCollision;
	timeCollision = COnCollision::GetInstance()->SweepAABB(this->simon->GetBox(), this->GetBox(), normalX, normalY, deltaTime);
	if (normalY == CDirection::ON_UP || normalY == CDirection::ON_DOWN)
	{
		CSimon::GetInstance()->isDie = true;
		CSimon::GetInstance()->isSimonDie = true;
		CSimon::GetInstance()->m_countLife -= 1;
	}
}
