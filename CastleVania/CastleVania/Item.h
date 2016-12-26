#pragma once
#ifndef __CITEM_H__
#define __CITEM_H__
#include "BaseGameObject.h"
#include "Move.h"
#include "Animation.h"

enum class ITEM_name
{
	SmallHeart = 301,
	LargeHeart = 302,
	MagicalCrystal = 303,
	//MoneyBag
	MoneyBag = 305,
	MoneyBagBlue = 351,
	MoneyBagRed = 352,
	MoneyBagWhite = 353,

	MoneyBagPoint = 3050,
	MoneyBagPointRed = 3051,
	MoneyBagPointWhite = 3052,
	MoneyBagPointBlue = 3053,
	//!MoneyBag
	PorkChop = 309,
	MorningStar = 310,
	Dagger = 312,
	Axe = 315,
	Cross = 316,
	Boomerang = 314,
	FireBomb = 313,
	None = 0

};
class CItem : public CBaseGameObject, public CMove, public CAnimation
{
public:
	CItem();
	CItem(ITEM_name itemName, Vector2 pos);
	~CItem();
public:
	float m_current_time_life;
	ITEM_name itemName;
public:
	void Init();
	void Update(float deltaTime);
	virtual void MoveUpdate(float deltaTime);
	Box GetBox();
	RECT* GetRectRS();

};

#endif // !__CITEM_H__