#ifndef __BLACKLEOPARD_H__
#define __BLACKLEOPARD_H__
#include "Enemy.h"
class CBlackLeopard :
	public CEnemy
{
public:
	CBlackLeopard();
	CBlackLeopard(Vector2 pos);
	~CBlackLeopard();
public:
	void Init();
	RECT* GetRectRS();
};

#endif // !__BLACKLEOPARD_H__

