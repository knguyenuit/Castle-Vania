#ifndef __ENEMY_H__
#define __ENEMY_H__
#include "BaseGameObject.h"
#include "Move.h"
#include "DrawObject.h"
#include "Animation.h"
#include "Item.h"

enum ENEMY_type
{
	Zombie = 201,
	BlackLeopard = 202,
	VampireBat = 203,
	Medusa = 204,
	FishMan = 205,
	AxeMan = 206,
	DragonSkullCanon = 207,
	BlackKnight = 208,
	WhiteSkeleton = 209,
	Ghost = 210,
	FireBall = 211,
	Bullet = 212,
	BossVampireBat = 401,
	BossLevel2 = 402,
	SmallLight = 600
};

enum class ENEMY_state {
	IDLE = 1,
	MOVE = 2,
	JUMP = 3,
	FREE = 4,
	ATTACK = 5
};

class CEnemy : public CBaseGameObject, public CMove, public CAnimation
{
public:
	ENEMY_state m_State;
	
	ENEMY_type enemyType;
	ITEM_name enemyItem = ITEM_name::None;
public:
	CDrawObject* drawEnemyManage;
	bool check_arrive_x = false;
	bool check_arrive_y = false;
public:
	void changeState(ENEMY_state state);
public:
	CEnemy();
	void Init();
	void InitAnimation();
	void Update(float deltaTime);
	bool MoveTo(Vector2 point, float deltaTime);
	virtual void MoveUpdate(float deltaTime);
	void OnSimonCollision(float deltaTime);
	void OnCaneCollision();
	RECT* GetRectRS();
	~CEnemy();

};

#endif