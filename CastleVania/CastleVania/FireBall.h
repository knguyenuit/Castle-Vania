#ifndef __FIREBALL_H__
#define __FIREBALL_H__

#include "Enemy.h"

class CFireBall :
	public CEnemy
{
public:
	CFireBall();
	CFireBall(Vector2 pos, Direction dir);
	CFireBall(Vector2 pos, Direction dir, float v_x, float v_y);
	void Init();
	~CFireBall();
public:
	void Draw();
	void Update(float deltaTime);
	void MoveUpdate(float deltaTime);
	RECT * GetRectRS();
	CSprite * m_draw;
};

#endif // !__FIREBALL_H__

