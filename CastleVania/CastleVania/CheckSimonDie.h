#pragma once
#include "HideObject.h"
#include "Simon.h"
class CCheckSimonDie : public CHideObject
{
public:
	CCheckSimonDie();
	CCheckSimonDie(HideObject_TYPE type, Vector2 pos);
	~CCheckSimonDie();
public:
	void Update(float deltaTime);
	void OnSimonCollision(float deltaTime);
};

