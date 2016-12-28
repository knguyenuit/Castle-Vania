#pragma once
#include "HideObject.h"
#include "EnemyManage.h"
#include "GroundMovingManage.h"

class CBrickVertical : public CHideObject
{
public:
	CBrickVertical();
	CBrickVertical(Vector2 pos, int m_Width, int m_Height);
	~CBrickVertical();
public:
	Box GetBox();
	void Init();
	RECT* GetRectRS();
	void Update(float deltaTime);
public:
	void OnSimonCollision(float deltaTime);
	void OnEnemyCollision(float deltaTime, std::vector<CEnemy*> listEnemy);
	void OnGroundMovingCollision(float deltaTime, std::vector<CGroundMovingPlatform*> listGroundMoving);
};

