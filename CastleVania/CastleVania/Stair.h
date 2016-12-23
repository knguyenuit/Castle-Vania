#ifndef __STAIR_H__
#define __STAIR_H__

#include "HideObject.h"
class CStair :
	public CHideObject
{
public:
	CStair();
	CStair(HideObject_TYPE type, Vector2 pos);
	~CStair();
public:
	void Init();
	void OnSimonCollision(float deltaTime);
	void Update(float deltaTime);
	bool SimonMoveOnStair(float deltaTime);
	bool SimonMoveToStair(float deltaTime);
	bool SimonMoveOutStair(float deltaTime);
	void ResetSimonStair();
public:
	bool isCancelSimonMove = true;
};

#endif // !__STAIR_H__
