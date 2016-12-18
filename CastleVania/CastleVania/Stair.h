#pragma once
#include "HideObject.h"
class CStair :
	public CHideObject
{
public:
	CStair();
	CStair(HideObject_TYPE type, Vector2 pos);
	~CStair();
public:
	void OnSimonCollision(float deltaTime);
	void Update(float deltaTime);
	void SimonMove(float deltaTime);
	void MoveUpStairRight(float deltaTime);
	void MoveDownStairLeft(float deltaTime);
	void MoveDownStairRight(float deltaTime);
	void MoveUpStairLeft(float deltaTime);
	void resetCanStair();
};

