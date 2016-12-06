#include "Item.h"
#include "ItemManage.h"


CItem::CItem()
{
	Init();
	
}


CItem::CItem(ITEM_name itemName, Vector2 pos)
{
	Init();
	this->m_PosDefault = this->m_Pos = pos;
	this->m_vyDefault = this->m_vy = 100;
	switch (itemName)
	{
	case ITEM_name::SmallHeart:
		this->m_Width = 16;
		this->m_Height = 16;
		this->m_Id = (int)itemName;
		this->m_RectRS = GetRectRS();
		break;
	case ITEM_name::LargeHeart:
		this->m_Width = 24;
		this->m_Height = 20;
		this->m_Id = (int)itemName;
		this->m_RectRS = GetRectRS();
		break;
	case ITEM_name::MorningStar:
		this->m_Width = 32;
		this->m_Height = 32;
		this->m_Id = (int)itemName;
		this->m_RectRS = GetRectRS();
		break;
	case ITEM_name::Dagger:
		this->m_Width = 32;
		this->m_Height = 18;
		this->m_Id = (int)itemName;
		this->m_RectRS = GetRectRS();
		break;
	default:
		break;
	}
}


void CItem::Init()
{
	this->m_vxDefault = 0;
	this->m_vyDefault = 10;
	this->m_isRemove = false;
	this->m_current_time_life = 0.0f;
}

void CItem::Update(float deltaTime)
{
	
	this->m_current_time_life += deltaTime;
	if (this->m_current_time_life >= 3.0f)
	{
		this->m_isRemove = true;
	}
	MoveUpdate(deltaTime);
}

void CItem::MoveUpdate(float deltaTime)
{

	if (this->m_Pos.y > 48) {
		this->m_Pos.y -= this->m_vyDefault * deltaTime;
		this->m_Pos.x = this->m_PosDefault.x + std::sin((this->m_Pos.y-this->m_PosDefault.y)/50*PI) * 30;
	}
	
}

Box CItem::GetBox()
{
	return Box(this->m_Pos.x, this->m_Pos.y, this->m_Width - 2, this->m_Height-2);
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
