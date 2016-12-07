#pragma once
#include "BaseGameObject.h"

class CBrick : public CBaseGameObject
{


public:
	CBrick();
	CBrick(Vector2 pos);
	~CBrick();
public:
	Box GetBox();
	void Init();
	RECT* GetRectRS();
	void Update(float deltaTime);
};

