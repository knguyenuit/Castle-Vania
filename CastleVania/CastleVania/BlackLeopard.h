#pragma once
#include "Enemy.h"
class CBlackLeopard :
	public CEnemy
{
public:
	CBlackLeopard();
	CBlackLeopard(Vector2 pos);
	~CBlackLeopard();
public:
	void Init();
	RECT* GetRectRS();
public:
	virtual void MoveUpdate(float deltaTime);
};

