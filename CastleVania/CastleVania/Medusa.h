#pragma once
#include "Enemy.h"

class CMedusa : public CEnemy
{
public:
	CMedusa();
	~CMedusa();
	CMedusa(Vector2 pos);
public:
	void Init();
	RECT* GetRectRS();
public:
	virtual void MoveUpdate(float deltaTime);
};

