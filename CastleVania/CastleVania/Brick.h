#pragma once
#include "HideObject.h"
#include "ItemManage.h"
#include "EnemyManage.h"
class CBrick :
	public CHideObject
{


public:
	CBrick();
	CBrick(Vector2 pos);
	~CBrick();
public:
	CSimon* simon = CSimon::GetInstance();
	Box GetBox();
	void Init();
	RECT* GetRectRS();
	void Update(float deltaTime);
public:
	void OnSimonCollision(float deltaTime);
	void OnItemCollision(float deltaTime, std::vector<CItem*> listItem);
	void OnEnemyCollision(float deltaTime, std::vector<CEnemy*> listEnemy);
};

