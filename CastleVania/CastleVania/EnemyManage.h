#ifndef __ENEMYMANAGE_H__
#define __EMEMYMANAGE_H__
#include "Enemy.h"
#include "Singleton.h"
#include "Zombie.h"
#include "BlackLeopard.h"
#include "VampireBat.h"
#include "BossVampireBat.h"
#include "Resources.h"
#include "OnCollision.h"
#include "Simon.h"
class CEnemyManage : public CSingleton<CEnemyManage>
{
	friend class CSingleton<CEnemyManage>;
public:
	CEnemyManage();
	~CEnemyManage();
public:
	CEnemy* currentEnemy;
	std::vector<CEnemy*> m_ListEnemy;
public:
	void OnCaneCollision();
	void OnSimonCollision(float deltaTime);
	void CreateEnemy(ENEMY_type enemyType, Vector2 pos);
	void DrawEnemy(CEnemy* enemyObj);
	void Draw();
	void Update(float deltaTime);
	CSprite* m_draw;
};

#endif // !__ENEMYMANAGE_H__

