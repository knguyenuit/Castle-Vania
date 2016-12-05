#ifndef __CVAMPIREBAT_H__
#define __CVAMPIREBAT_H__

#include "Enemy.h"
class CVampireBat :
	public CEnemy
{
public:
	CVampireBat();
	CVampireBat(Vector2 pos);
	~CVampireBat();
public:
	void Init();
	RECT* GetRectRS();
public:
	virtual void MoveUpdate(float deltaTime);
};

#endif // !__CVAMPIREBAT