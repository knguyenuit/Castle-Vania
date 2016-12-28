#include "GroundMovingManage.h"



CGroundMovingManage::CGroundMovingManage()
{
}


CGroundMovingManage::~CGroundMovingManage()
{
}

CGroundMovingPlatform * CGroundMovingManage::CreateGroundMovingPlatform(Vector2 pos)
{
	CGroundMovingPlatform* gr;
	gr = new CGroundMovingPlatform(pos);
	this->m_ListGroundMovingPlatform.push_back(gr);
	return gr;
}
