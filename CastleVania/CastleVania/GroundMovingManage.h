#pragma once
#include "GroundMovingPlatform.h"
#include "Singleton.h"

class CGroundMovingManage : public CSingleton<CGroundMovingManage>
{
	friend class CSingleton<CGroundMovingManage>;
public:
	CGroundMovingManage();
	~CGroundMovingManage();
public:
	std::vector<CGroundMovingPlatform*> m_ListGroundMovingPlatform;
	CGroundMovingPlatform* CreateGroundMovingPlatform( Vector2 pos);
};
