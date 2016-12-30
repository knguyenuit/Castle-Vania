#pragma once
#include "HideObject.h"
#include "Camera.h"
class CStopScrollCamera : public CHideObject
{
public:
	CStopScrollCamera();
	CStopScrollCamera(HideObject_TYPE type, Vector2 pos);
	~CStopScrollCamera();

public:
	void Update(float deltaTime);
	void OnSimonCollision(float deltaTime);
};

