#ifndef __BOSSMEDUSA_H__
#define __BOSSMEDUSA_H__

#include "Enemy.h"
#include "SnakeManage.h"
#include "Singleton.h"
class CBossMedusa :
	public CEnemy, public CSingleton<CBossMedusa>
{
	friend class CSingleton<CBossMedusa>;
public:
	CBossMedusa();
	CBossMedusa(Vector2 pos);
	~CBossMedusa();
	void Init();
	RECT * GetRectRS();
	void MoveUpdate(float deltaTime);
	void Update(float deltaTime);
public:
	CCamera *camera = CCamera::GetInstance();
	int m_Step = 1;
	Vector2 m_StepPos[4];
	bool m_isAttacking = false;
	Vector2 current_step_pos, next_step_pos;
	float m_pos_x_prepare_attack[5] = { -280,-150,0,150,280 };
	float m_pos_y_prepare_attack[5] = { 10,10,10,10,10 };
	float time_delay_step = 0.3f;
	void OnSimonCollision(float deltaTime);
	void OnCaneCollision(float deltaTime);
	void OnWeaponCollision(float deltaTime, std::vector<CWeapon*> listWeapon);

	//time count
	float timeCount = 0;
};

#endif // !__BOSSMEDUSA_H__
