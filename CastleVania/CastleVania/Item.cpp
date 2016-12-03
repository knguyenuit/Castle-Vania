#include "Item.h"


CItem::CItem()
{
	Init();
}


CItem::CItem(ITEM_name itemName, Vector2 pos)
{
	switch (itemName)
	{
	case ITEM_name::SmallHeart:
		this->m_Width = 16;
		this->m_Height = 16;
		this->m_Id = (int)itemName;
		this->m_Pos = pos;
		this->m_RectRS = GetRectRS();
		break;
	case ITEM_name::LargeHeart:
		this->m_Width = 24;
		this->m_Height = 20;
		this->m_Id = (int)itemName;
		this->m_Pos = pos;
		this->m_RectRS = GetRectRS();
		break;
	case ITEM_name::MorningStar:
		this->m_Width = 32;
		this->m_Height = 32;
		this->m_Id = (int)itemName;
		this->m_Pos = pos;
		this->m_RectRS = GetRectRS();
		break;
	case ITEM_name::Dagger:
		this->m_Width = 32;
		this->m_Height = 18;
		this->m_Id = (int)itemName;
		this->m_Pos = pos;
		this->m_RectRS = GetRectRS();
		break;
	default:
		break;
	}
}


void CItem::Init()
{
	this->m_vx = 0;
	this->m_vy = 10;
	this->m_IsActive = false;
}

void CItem::Update(float deltaTime)
{
	MoveUpdate(deltaTime);
}

void CItem::MoveUpdate(float deltaTime)
{
	this->m_Pos.y -= this->m_vy * deltaTime;
}

RECT * CItem::GetRectRS()
{
	RECT * rec = new RECT();
	rec->left = 0;
	rec->right = rec->left + m_Width;
	rec->top = 0;
	rec->bottom = rec->top + m_Height;
	return rec;
}





CItem::~CItem()
{
}
