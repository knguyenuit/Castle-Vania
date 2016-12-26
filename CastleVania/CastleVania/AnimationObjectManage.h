#ifndef __ANIMATIONOBJECTMANAGE_H__
#define __ANIMATIONOBJECTMANAGE_H__
#include "Singleton.h"
#include "Camera.h"
#include "FireOnAnimate.h"
#include "RockFallAnimate.h"
#include "Resources.h"
class CAnimationObjectManage :
	public CSingleton<CAnimationObjectManage>
{
	friend class CSingleton<CAnimationObjectManage>;
public:
	CAnimationObjectManage();
	~CAnimationObjectManage();
public:
	std::vector<CAnimationObject*> m_listAnimationObject;
	void Update(float deltaTime);
	CAnimationObject* CreateAnimation(Animation_object animationType, Vector2 pos);
	CAnimationObject* CreateAnimation(Animation_object animationType, Vector2 pos, ITEM_name itemName);
	void DrawAnimationObject(CAnimationObject* animationObj);
	void Draw();
	CTexture* Texture = new CTexture();
	Vector3 posDraw = Vector3();
	CSprite * m_draw;
};

#endif // !__ANIMATIONOBJECTMANAGE_H__
