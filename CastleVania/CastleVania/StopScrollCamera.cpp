#include "StopScrollCamera.h"



CStopScrollCamera::CStopScrollCamera()
{
}

CStopScrollCamera::CStopScrollCamera(HideObject_TYPE type, Vector2 pos)
{
	this->m_Width = 32;
	this->m_Height = 96;
	this->m_typeHideObject = type;
	this->m_Pos = pos;
}


CStopScrollCamera::~CStopScrollCamera()
{
}

void CStopScrollCamera::Update(float deltaTime)
{
	OnSimonCollision(deltaTime);
}

void CStopScrollCamera::OnSimonCollision(float deltaTime)
{
	CDirection normalX;
	CDirection normalY;
	float timeCollision;
	timeCollision = COnCollision::GetInstance()->SweepAABB(this->simon->GetBox(), this->GetBox(), normalX, normalY, deltaTime);
	if (normalX == CDirection::ON_LEFT || normalX == CDirection::ON_RIGHT)
	{

		CCamera::GetInstance()->isStopScrollCamera = true;
	}
}
