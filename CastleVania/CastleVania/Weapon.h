#ifndef __WEAPON_H__
#define __WEAPON_H__

#include "BaseGameObject.h"
#include "Animation.h"
#include "Move.h"
#include "Simon.h"

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
	WEAPON_name m_WeaponName = WEAPON_name::None;
	float m_time_life;
	bool boomerang_turn_back = false;
public:
	void Init();
	void InitAnimate(int totalFrame, int column, int startFrame, int endFrame);
	void Update(float deltaTime);
	virtual void MoveUpdate(float deltaTime);
	Box GetBox();
	RECT* GetRectRS();
	
};
#endif // !__WEAPON_H__

