#include "Item.h"


CItem::CItem()
{
}


void CItem::Init()
{
	this->m_vx = 0;
	this->m_vy = 10;
	
}

void CItem::Update(float deltaTime)
{
	this->m_Pos.y -= this->m_vy * deltaTime;
}





CItem::~CItem()
{
}
