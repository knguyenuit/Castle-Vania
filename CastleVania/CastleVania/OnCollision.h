#ifndef __CONCOLLISION_H__
#define __CONCOLLISION_H__
#include "Global.h"
#include "Singleton.h"
#include "BaseGameObject.h"

enum CDirection
{
	// Hướng lên
	ON_UP = 101,
	// Hướng xuống
	ON_DOWN = 102,
	// Hướng bên phải
	ON_RIGHT = 103,
	// Hướng bên trái
	ON_LEFT = 104,
	NONE_DIRECT = 105,
	// Hai vật nằm lồng trong nhau
	INSIDE = 106
};

class COnCollision : public CSingleton<COnCollision>
{
	friend class CSingleton<COnCollision>;
public:
	COnCollision();
	~COnCollision();
public:
	bool AABBCheck(Box box1, Box box2);
	float SweepAABB(Box box1, Box box2, CDirection &normalX, CDirection &normalY, float frameTime);
	float SweepAABB(CBaseGameObject* obj1, CBaseGameObject* obj2, CDirection &normalX, CDirection &normalY, float frameTime);
};

#endif