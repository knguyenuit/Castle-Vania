#ifndef __FIREONANIMATE_H__
#define __FIREONANIMATE_H__

#include "AnimationObject.h"
class CFireOnAnimate :
	public CAnimationObject
{
public:
	CFireOnAnimate();
	CFireOnAnimate(Vector2 pos);
	~CFireOnAnimate();
	void Init();
	RECT* GetRectRS();
};
#endif // !__FIREONANIMATE_H__
