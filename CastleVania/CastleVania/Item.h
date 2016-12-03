#pragma once
#ifndef __CITEM_H__
#define __CITEM_H__
#include "BaseGameObject.h"
#include "Move.h"

class CItem : public CBaseGameObject, public CMove
{
public:
	CItem();
	CItem(ITEM_name itemName, Vector2 pos);
	~CItem();
public:
	bool m_IsActive;
public:
	void Init();
	void Update(float deltaTime);
	virtual void MoveUpdate(float deltaTime);
	RECT* GetRectRS();
	
};

#endif // !__CITEM_H__