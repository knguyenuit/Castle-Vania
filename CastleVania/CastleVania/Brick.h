#pragma once
#include "BaseGameObject.h"
#include "OnCollision.h"
#include "Simon.h"
class CBrick : public CBaseGameObject
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
};

