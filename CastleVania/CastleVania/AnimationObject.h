#ifndef __ANIMATIONOBJECT_H__
#define __ANIMATIONOBJECT_H__

#include "BaseGameObject.h"
#include "Animation.h"
#include "Sprite.h"
#include "Simon.h"
#include "ItemManage.h"
#include "ManageAudio.h"
enum class Animation_object {
	FireOn = 1,
	RockFall = 2,
	MoneyBagPoint = 3,
	None = 0
};
class CAnimationObject :
	public CBaseGameObject, public CAnimation
{
public:
	CAnimationObject();
	~CAnimationObject();
	ITEM_name itemName = ITEM_name::None;
	void Update(float deltaTime);
public:
	Animation_object m_typeAnimationObject = Animation_object::None;
	float m_timeLife = 0.0f;
	float m_timeExist = 0.5f;
	RECT* GetRectRS();
};
#endif // !__ANIMATIONOBJECT_H__

