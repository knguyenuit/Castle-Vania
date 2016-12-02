#pragma once
#include "BaseGameObject.h"
#include "Collision.h"
#include "Move.h"
#include "Animation.h"

class CHinhVuong : public CBaseGameObject, public CMove, CAnimation
{
public:
	void Init();
	void Update(float deltaTime);
	CHinhVuong();
	~CHinhVuong();
	RECT* GetRectRS()
	{

		RECT* rectRS = new RECT();


		//cập nhật lại vị trí của Rect Resource
		rectRS->left = 0;
		rectRS->right =  this->m_Width;
		rectRS->top = 0;
		rectRS->bottom = this->m_Height;
		return rectRS;
	}
	virtual void MoveUpdate(float deltaTime);
	virtual Box GetBox();
};

