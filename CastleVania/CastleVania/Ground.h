#ifndef __CGROUND_H__
#define __CGROUND_H__
#include "BaseGameObject.h"
#include "Animation.h"
#include "Simon.h"
#include "ItemManage.h"
#include "ManageAudio.h"
#include "AnimationObjectManage.h"
class CGround : public CBaseGameObject, CAnimation
{
public:
	CSimon* simon = CSimon::GetInstance();
	CGround();
	CGround(Vector2 pos);
	~CGround();
public:
	Box GetBox();
	RECT* GetBound();
	RECT* GetRectRS();
public:
	void Init();
	void InitAnimation();
	void Update(float deltaTime);
	void OnCaneCollision(float deltaTime);
};

#endif // !__CGROUND_H__
