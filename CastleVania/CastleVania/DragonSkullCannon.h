#pragma once
#include "Enemy.h"
#include "FireBallManage.h"

class CDragonSkullCannon : public CEnemy
{
public:
	CDragonSkullCannon();
	CDragonSkullCannon(Vector2 pos);
	~CDragonSkullCannon();
public:
	float timeCountIntanceFireBall = 0; // thoi gian instance ra 1 fire ball
	Vector2 posIntanceFireBall1;
	Vector2 posIntanceFireBall2;
public:
	void Init();
	void Update(float deltaTime);

};

