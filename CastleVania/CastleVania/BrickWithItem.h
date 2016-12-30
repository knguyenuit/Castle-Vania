#ifndef __BRICKWITHITEM_H__
#define __BRICKWITHITEM_H__

#include "AnimationObject.h"
class CBrickWithItem :
	public CAnimationObject
{
public:
	CBrickWithItem();
	CBrickWithItem(Vector2 pos);
	~CBrickWithItem();

	void Init();
	CSimon * simon = CSimon::GetInstance();
	void Update(float deltaTime);
	void OnCaneCollision(float deltaTime);
	void OnSimonCollision(float deltaTime);
	float isCaneCollision = false;
};

#endif // !__BRICKWITHITEM_H__