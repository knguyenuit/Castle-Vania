#pragma once
#include "HideObject.h"
#include "Simon.h"
class CChangeDown : public CHideObject
{
public:
	CChangeDown();
	CChangeDown(HideObject_TYPE type, Vector2 pos);
	~CChangeDown();

public:
	void Update(float deltaTime);
	void OnSimonCollision(float deltaTime);
};

