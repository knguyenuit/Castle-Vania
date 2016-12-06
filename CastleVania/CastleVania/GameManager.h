#ifndef __CGAMEMANAGER_H__
#define __CGAMEMANAGER_H__

#include "PoolObject.h"
#include "DrawObject.h"
#include "LoadBackground.h"
#include "Singleton.h"
#include "Level.h"


class CGameManager : public CSingleton<CGameManager>
{
	friend class CSingleton<CGameManager>;
public:
	CGameManager();
	~CGameManager();



	bool isCheck = false;

public:
	Level* m_currentLevel;
	int m_Level;
	void Init();
	void Update(float deltaTime);
	void Draw();
	void ChangeLevel(int lv);
};

#endif // !__CGAMEMANAGER_H__