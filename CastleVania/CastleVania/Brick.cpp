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
	return Box(this->m_Pos.x, this->m_Pos.y, this->m_Width, this->m_Height);
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
}

void CBrick::OnSimonCollision(float deltaTime)
{
	CDirection normalX;
	CDirection normalY;
	float timeCollision;
	timeCollision = COnCollision::GetInstance()->SweepAABB(this->simon->GetBox(), this->GetBox(), normalX, normalY, deltaTime);
	if (normalY == CDirection::ON_DOWN)
	{
		simon->isFree = false;
		simon->canJump = true;
	}
}
