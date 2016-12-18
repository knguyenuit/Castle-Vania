#ifndef __SMALLLIGHT_H__
#define __SMALLLIGHT_H__

#include "Enemy.h"
class CSmallLight : public CEnemy
{
public:
	CSmallLight();
	CSmallLight(Vector2 pos);
	CSmallLight(Vector2 pos, ITEM_name enemyItem);
	void Init();
	~CSmallLight();
public:
	RECT * GetRectRS();
public:
	void Update(float deltaTime);
};

#endif // !__SMALLLIGHT_H__

