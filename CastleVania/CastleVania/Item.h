#pragma once
#ifndef __CITEM_H__
#define __CITEM_H__
#include "BaseGameObject.h"
#include "Move.h"

enum ITEM_name
{
	SmallHeart = 301,
	LargeHeart = 302,
	MoneyBag = 305,
	Axe = 315,
	PorkChop = 309,
	MorningStar = 310,
	Dagger = 312,
	Cross = 316

};

class CItem : public CBaseGameObject, public CMove
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