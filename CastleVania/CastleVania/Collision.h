#ifndef __CCOLLISION_H__
#define __CCOLLISION_H__

#define NOMINMAX

#include "Collision.h"
#include "Global.h"
#include "BaseGameObject.h"
#include "Singleton.h"

class CCollision : public CSingleton<CCollision>
{
	friend class CSingleton<CCollision>;
public:
	float SweptAABB(Box first, Box second, float& normalx, float& normaly, float deltaTime);
	Box GetSweptBroadphaseBox(Box box, float deltaTime);
	bool AABBCheck(Box b1, Box b2, float& moveX, float& moveY, float& normalX, float& normalY);
	bool AABBCheck(Box b1, Box b2);
	//////
	bool AABB(Box b1, Box b2, float& moveX, float& moveY);
	float sweptAABB(Box b1, Box b2, float& normalx, float& normaly, float deltaTime);
	float Collision(CBaseGameObject* ObjectA, CBaseGameObject* ObjectB, float &normalx, float &normaly, float deltaTime);
	float Collision(Box b1, Box b2, float & normalx, float & normaly, float deltaTime);
	/////

	float Collision(CBaseGameObject* ObjectA, CBaseGameObject* ObjectB, float& normalx, float& normaly, float& moveX, float& moveY, float deltaTime);
	float Collision(Box ObjectA, Box ObjectB, float& normalx, float& normaly, float& moveX, float& moveY, float deltaTime);
	CCollision();
	~CCollision();
private:

};

#endif // !__CCOLLISION_H__