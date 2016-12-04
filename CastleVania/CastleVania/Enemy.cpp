#include "Enemy.h"



CEnemy::CEnemy()
{
}

void CEnemy::InitAnimation()
{
	
}

void CEnemy::Update(float deltaTime)
{
	ChangeFrame(deltaTime);
}

RECT * CEnemy::GetRectRS(float height, float width)
{
	return this->UpdateRectResource(height,width);
}



CEnemy::~CEnemy()
{
}
