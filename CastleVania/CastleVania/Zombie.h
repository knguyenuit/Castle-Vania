#ifndef __ZOMBIE_H__
#define __ZOMBIE_H__
#include "Enemy.h"

class CZombie : public CEnemy
{
public:
	CZombie();
	CZombie(Vector2 pos);
	~CZombie();
public:
	void Init();
	RECT* GetRectRS();
};

#endif // !__ZOMBIE_H__