#ifndef __UPSTAIRRIGHT_H__
#define __UPSTAIRRIGHT_H__

#include "Stair.h"
class CUpStairRight :
	public CStair
{
public:
	CUpStairRight();
	CUpStairRight(Vector2 pos);
	~CUpStairRight();
public:
	void Update(float deltaTime);
	bool SimonMoveOnStair(float deltaTime);
	bool SimonMoveToStair(float deltaTime);
	bool SimonMoveOutStair(float deltaTime);
};
#endif // !__UPSTAIRRIGHT_H__
