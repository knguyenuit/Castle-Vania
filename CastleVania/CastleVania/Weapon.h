#ifndef __WEAPON_H__
#define __WEAPON_H__

#include "BaseGameObject.h"
#include "Animation.h"
#include "Move.h"
enum class WEAPON_name
{
	Axe = 505,
	Boomerang = 506,
	Dagger = 507,
	FireBomb = 508,
	Watch = 509,
	FireBomb2 = 511,
	None = 0
};
class CWeapon :
	public CBaseGameObject,
	public CAnimation,
	public CMove
{
public:
	CWeapon();
	CWeapon(WEAPON_name weaponName, Vector2 pos);
	~CWeapon();
public:
	WEAPON_name m_WeaponName;
	float m_time_life;
public:
	void Init();
	void InitAnimate(int totalFrame, int column, int startFrame, int endFrame);
	void Update(float deltaTime);
	virtual void MoveUpdate(float deltaTime);
	Box GetBox();
	RECT* GetRectRS();
};
#endif // !__WEAPON_H__

