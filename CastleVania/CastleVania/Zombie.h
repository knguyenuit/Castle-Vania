#ifndef __ZOMBIE_H__
#define __ZOMBIE_H__
#include "Enemy.h"
#endif // !__ZOMBIE_H__
class CZombie : public CEnemy
{
public:
	CZombie();
	CZombie(Vector2 pos);
	~CZombie();
public:
	void Init();
public:
	void MoveUpdate(float deltaTime);
	//RECT* GetRectRS();
};

