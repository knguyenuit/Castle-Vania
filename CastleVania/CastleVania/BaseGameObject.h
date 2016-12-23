#ifndef __CBASEGAMEOBJECT__H__
#define __CBASEGAMEOBJECT__H__
#include "Global.h"

enum Direction
{
	NONE_DIR = 0,
	LEFT = 1,
	RIGHT = 2,
};

class CBaseGameObject
{
public:
	int m_Id;// id cua Object. dung de load hinh anh
	Vector2 m_Pos;//vi tri
	Vector2 m_PosDefault; //vi tri ban dau
	Direction m_Dir;//dang huong ve phia nao
	bool m_isLive; // check xem doi tuong con song hay ko?
	bool isLeft, isRight, isUp, isDown; // direction, default left // direction, default left
	float m_Width;//chieu rong cua hinh
	float m_Height;//chieu cao cua hinh

				   //do dai that de xet va cham
	float m_realWidth;
	float m_realHeight;

	RECT *m_RectRS;//de xet va cham

	bool m_isRemove; //xoa' doi' tuong.

public:
	CBaseGameObject();
	~CBaseGameObject();
	int GetID() { return this->m_Id; };
	Direction GetDirection() { return this->m_Dir; };
	bool IsLive() { return this->m_isLive; };
	bool isRemove() { return this->m_isRemove; }
	virtual void Update(float deltaTime);//ham Update chinh cua game

	virtual void SetPos(Vector2 pos);
	virtual Vector2 GetPos();

	int GetWidth() { return this->m_Width; };
	int GetHeight() { return this->m_Height; };

	virtual Box GetBox();
	virtual RECT* GetBound();
	virtual RECT* GetRectRS();
};
#endif // !__OBJECT_GAME__H__

