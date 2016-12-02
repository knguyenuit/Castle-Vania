#pragma once
#ifndef __CITEM_H__
#define __CITEM_H__
#include "BaseGameObject.h"
#include "Move.h"

class CItem : public CBaseGameObject, public CMove
{
public:
	void Init();
	void Update(float deltaTime);
	CItem();
	~CItem();
};

#endif // !__CITEM_H__