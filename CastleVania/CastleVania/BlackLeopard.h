#pragma once
#include "Enemy.h"
class CBlackLeopard :
	public CEnemy
{
public:
	CBlackLeopard();
	~CBlackLeopard();
public:
	void Init();
	RECT* GetRectRS();
public:
	virtual void MoveUpdate(float deltaTime);
};

