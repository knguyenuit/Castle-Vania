#ifndef __DOWNSTAIRLEFT_H__
#define __DOWNSTAIRLEFT_H__

#include "Stair.h"
class CDownStairLeft :
	public CStair
{
public:
	CDownStairLeft();
	CDownStairLeft(Vector2 pos);
	~CDownStairLeft();
public:
	void Update(float deltaTime);
	bool SimonMoveOnStair(float deltaTime);
	bool SimonMoveToStair(float deltaTime);
	bool SimonMoveOutStair(float deltaTime);
};
#endif // !__DOWNSTAIRLEFT_H__

