#ifndef __ENEMY_H__
#define __ENEMY_H__
#include "BaseGameObject.h"
#include "Move.h"
#include "DrawObject.h"
#include "Animation.h"
class CEnemy : public CBaseGameObject, public CMove, public CAnimation
{
public:
	bool m_IsActive = false;
	bool m_IsAlive = true;
	bool m_isRemove = false;
	ENEMY_type enemyType;
public:
	CDrawObject* drawEnemyManage;
public:
	CEnemy();
	void InitAnimation();
	void Update(float deltaTime);
	virtual void MoveUpdate(float deltaTime);
	RECT* GetRectRS();
	~CEnemy();

};

#endif