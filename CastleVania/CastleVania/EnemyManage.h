#ifndef __ENEMYMANAGE_H__
#define __EMEMYMANAGE_H__
#include "Enemy.h"
#include "Singleton.h"
class CEnemyManage : public CSingleton<CEnemyManage> 
{
public:
	CEnemyManage();
	~CEnemyManage();
public:
	CEnemy* currentEnemy;

public:
	void CreateEnemy(ENEMY_type enemyType, Vector2 pos);
	void DrawEnemy(CEnemy* enemyObj);
	void Draw();
	void Update(float deltaTime);
	CSprite* m_draw;
};

#endif // !__ENEMYMANAGE_H__

