#ifndef __CANIMATION_H__
#define __CANIMATION_H__

#include "Global.h"

class CAnimation
{
public:
	CAnimation();
	~CAnimation();
public:
	float m_elapseTimeChangeFrame;
	float m_currentTime;
	int m_increase;
	int m_totalFrame;
	int m_currentFrame;
	int m_startFrame;
	int m_endFrame;
	int m_column;
	bool isStopChangeFrame = false;
public:
	virtual void ChangeFrame(float deltaTime);		// ham chuyen frame.
	virtual RECT*& UpdateRectResource(int rsHeight, int rsWidth);	//cap nhat lai vi tri rect resources.


};

#endif // !__CANIMATION_H__
