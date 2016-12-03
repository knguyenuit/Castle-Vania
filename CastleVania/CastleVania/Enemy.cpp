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

RECT * CEnemy::GetRectRS()
{
	return nullptr;
}


CEnemy::~CEnemy()
{
}
