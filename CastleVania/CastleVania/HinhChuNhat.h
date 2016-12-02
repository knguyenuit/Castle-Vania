#pragma once
#include "BaseGameObject.h"
#include "Move.h"
class CHinhChuNhat : public CBaseGameObject, public CMove
{
public:
	CHinhChuNhat();
	~CHinhChuNhat();
	void Init();
	void Update(float deltaTime);
	virtual RECT* GetRectRS();
	virtual void MoveUpdate(float deltaTime) {}
	virtual Box GetBox();
};

