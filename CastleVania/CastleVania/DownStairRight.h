#ifndef __DOWNSTAIRRIGHT_H__
#define __DOWNSTAIRRIGHT_H__

#include "Stair.h"
class CDownStairRight :
	public CStair
{
public:
	CDownStairRight();
	CDownStairRight(Vector2 pos);
	~CDownStairRight();
public:
	void Update(float deltaTime);
	bool SimonMoveOnStair(float deltaTime);
	bool SimonMoveToStair(float deltaTime);
	bool SimonMoveOutStair(float deltaTime);
};
#endif // !__DOWNSTAIRLEFT_H__

