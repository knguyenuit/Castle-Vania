#ifndef __ENEMYMANAGE_H__
#define __EMEMYMANAGE_H__
#include "Enemy.h"
#include "Singleton.h"
#include "Zombie.h"
#include "BlackLeopard.h"
#include "VampireBat.h"
#include "Resources.h"
class CEnemyManage : public CSingleton<CEnemyManage> 
{
public:
	CEnemyManage();
	~CEnemyManage();
public:
	CEnemy* currentEnemy;
	std::vector<CEnemy*> m_ListEnemy;
public:
	void CreateEnemy(ENEMY_type enemyType, Vector2 pos);
	void DrawEnemy(CEnemy* enemyObj);
	void Draw();
	void Update(float deltaTime);
	CSprite* m_draw;
};

#endif // !__ENEMYMANAGE_H__

