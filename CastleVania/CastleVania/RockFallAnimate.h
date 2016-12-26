#ifndef __ROCKFALLANIMATE_H__
#define __ROCKFALLANIMATE_H__

#include "AnimationObject.h"
class CRockFallAnimate :
	public CAnimationObject
{
public:
	CRockFallAnimate();
	CRockFallAnimate(Vector2 pos);
	~CRockFallAnimate();
	void Init();
	CSimon * simon = CSimon::GetInstance();
	RECT* GetRectRS();
	Box GetBox();
	void Update(float deltaTime);
	void OnCaneCollision(float deltaTime);
	void OnSimonCollision(float deltaTime);
	float isCaneCollision = false;
};
#endif // !__ROCKFALLANIMATE_H__

