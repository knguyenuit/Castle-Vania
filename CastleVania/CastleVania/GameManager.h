#ifndef __CGAMEMANAGER_H__
#define __CGAMEMANAGER_H__

#include "PoolObject.h"
#include "DrawObject.h"
#include "LoadBackground.h"
#include "Singleton.h"

class CGameManager : public CSingleton<CGameManager>
{
	friend class CSingleton<CGameManager>;
public:
	CGameManager();
	~CGameManager();
public:
	void Init();
	void Update(float deltaTime);
	void Draw();
};

#endif // !__CGAMEMANAGER_H__