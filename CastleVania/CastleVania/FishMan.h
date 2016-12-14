#ifndef __FISHMAN_H__
#define __FISHMAN_H__

#include "Enemy.h"
#include "Simon.h"
#include "FireBall.h"
class CFishMan :
	public CEnemy
{
public:
	CFishMan();
	CFishMan(Vector2 pos, std::vector<CEnemy*> &ListEnemy);
	~CFishMan();
public:
	void Init();
	void Update(float deltaTime);
	virtual void MoveUpdate(float deltaTime);
	RECT * GetRectRS();
public:
	float time_delay_attack = 1.0f;
	CFireBall *m_FireBall = NULL;
	Sprite *m_draw;
	std::vector<CEnemy*> listEnemy;
};

#endif // !__FISHMAN_H__
