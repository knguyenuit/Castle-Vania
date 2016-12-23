#ifndef __UPSTAIRLEFT_H__
#define __UPSTAIRLEFT_H__

#include "Stair.h"
class CUpStairLeft :
	public CStair
{
public:
	CUpStairLeft();
	CUpStairLeft(Vector2 pos);
	~CUpStairLeft();
public:
	void Update(float deltaTime);
	bool SimonMoveOnStair(float deltaTime);
	bool SimonMoveToStair(float deltaTime);
	bool SimonMoveOutStair(float deltaTime);
};
#endif // !__UPSTAIRRIGHT_H__
