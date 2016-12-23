#pragma once
#include "HideObject.h"
class CChangeScreen : public CHideObject
{
public:
	CChangeScreen();
	CChangeScreen(HideObject_TYPE type, Vector2 pos);
	~CChangeScreen();
public:
	void Update(float deltaTime);
	void OnSimonCollision(float deltaTime);
};

