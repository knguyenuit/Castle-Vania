#include "BrickWithItemLv2.h"



CBrickWithItemLv2::CBrickWithItemLv2()
{
	this->Init();
}

CBrickWithItemLv2::CBrickWithItemLv2(Vector2 pos)
{
	this->m_typeAnimationObject = Animation_object::BrickItemLv2;
	this->m_Pos = pos;
	this->itemName = itemName;
	this->Init();
}


CBrickWithItemLv2::~CBrickWithItemLv2()
{
}
