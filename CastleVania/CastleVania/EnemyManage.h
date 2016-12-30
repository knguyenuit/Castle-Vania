#ifndef __ENEMYMANAGE_H__
#define __ENEMYMANAGE_H__
#include "Enemy.h"
#include "Singleton.h"
#include "Zombie.h"
#include "BlackLeopard.h"
#include "VampireBat.h"
#include "BossVampireBat.h"
#include "FishMan.h"
#include "SmallLight.h"
#include "Resources.h"
#include "OnCollision.h"
#include "Simon.h"
#include "ItemManage.h"
#include "BlackKnight.h"
#include "Medusa.h"
#include "DragonSkullCannon.h"
#include "BossMedusa.h"
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
	CEnemy* CreateEnemy(ENEMY_type enemyType, Vector2 pos);
	CEnemy* CreateEnemy(ENEMY_type enemyType, Vector2 pos, ITEM_name itemName);
	void DrawEnemy(CEnemy* enemyObj);
	void Draw();
	void Update(float deltaTime);
	CSprite* m_draw;
};

#endif // !__ENEMYMANAGE_H__

