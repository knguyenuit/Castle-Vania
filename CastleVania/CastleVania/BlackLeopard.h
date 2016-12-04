#ifndef __BLACKLEOPARD_H__
#define __BLACKLEOPARD_H_
#include "Enemy.h"
class CBlackLeopard : public CEnemy 
{
public:
	CBlackLeopard();
	CBlackLeopard(Vector2 pos);
	~CBlackLeopard();
public:
	void Init();
	virtual void MoveUpdate(float deltaTime);
};
#endif // !__BLACKLEOPARD_H__
