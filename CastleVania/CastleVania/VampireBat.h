#pragma once
#include "Enemy.h"
class CVampireBat :
	public CEnemy
{
public:
	CVampireBat();
	~CVampireBat();
public:
	void Init();
	RECT* GetRectRS();
public:
	virtual void MoveUpdate(float deltaTime);
};

