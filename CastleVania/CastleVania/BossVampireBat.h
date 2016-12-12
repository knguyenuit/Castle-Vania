#ifndef __BOSSVAMPIREBAT__H_
#define __BOSSVAMPIREBAT__H_
#include "Enemy.h"
#include "Simon.h"
class CBossVampireBat : public CEnemy
{
public:
	void Init();
	CBossVampireBat();
	CBossVampireBat(Vector2 pos);
	~CBossVampireBat();
public:
	int m_Step = 1;
	Vector2 m_StepPos[4];
	bool m_isAttacking = false;
	bool check_arrive_x = false;
	bool check_arrive_y = false;
	float m_pos_x_prepare_attack[5] = { -280,-150,0,150,280 };
	float m_pos_y_prepare_attack[5] = { 100,110,120,130,140 };
	float time_delay_step = 1.0f;
public:
	bool MoveTo(Vector2 point, float deltaTime);
	RECT* GetRectRS();
	void Update(float deltaTime);
	virtual void MoveUpdate(float deltaTime);
};
#endif //! __BOSSVAMPIREBAT__H_

