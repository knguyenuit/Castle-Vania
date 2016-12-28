#pragma once
#include "Move.h"
#include "BaseGameObject.h"
#include "Simon.h"
class CGroundMovingPlatform : public CBaseGameObject, public CMove
{
public:
	CGroundMovingPlatform();
	CGroundMovingPlatform(Vector2 pos);
	~CGroundMovingPlatform();
public:
	bool isChangeDir = false;
	CSimon* simon = CSimon::GetInstance();
	float distanceX = 0;
public:
	void Init();
	void Update(float deltaTime);
	void MoveUpdate(float deltaTime);
	Box GetBox();
	void OnSimonCollision(float deltaTime);
};

