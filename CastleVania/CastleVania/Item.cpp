#include "Item.h"
#include "ItemManage.h"


CItem::CItem()
{
	Init();
	
}


CItem::CItem(ITEM_name itemName, Vector2 pos)
{
	this->itemName = itemName;
	this->m_PosDefault = this->m_Pos = pos;
	Init();
}


void CItem::Init()
{
	switch (this->itemName)
	{
	case ITEM_name::SmallHeart:
		this->m_Width = 16;
		this->m_Height = 16;
		break;

	case ITEM_name::LargeHeart:
		this->m_Width = 24;
		this->m_Height = 20;
		break;

	case ITEM_name::MorningStar:
		this->m_Width = 32;
		this->m_Height = 32;
		break;

	case ITEM_name::Dagger:
		this->m_Width = 32;
		this->m_Height = 18;
		break;

	case ITEM_name::MoneyBag:
		this->m_Width = 30;
		this->m_Height = 30;
		break;

	case ITEM_name::Cross:
		this->m_Width = 32;
		this->m_Height = 32;
		break;

	case ITEM_name::Axe:
		this->m_Width = 30;
		this->m_Height = 28;
		break;

	case ITEM_name::PorkChop:
		this->m_Width = 32;
		this->m_Height = 26;
		break;
	default:
		break;
	}
	this->m_Id = (int)itemName;
	this->m_RectRS = GetRectRS();
	this->m_vxDefault = 0;
	this->m_vyDefault = 50;
	this->m_isRemove = false;
	this->m_current_time_life = 0.0f;
}

void CItem::Update(float deltaTime)
{
	
	this->m_current_time_life += deltaTime;
	if (this->m_current_time_life >= 5.0f)
	{
		this->m_isRemove = true;
	}
	MoveUpdate(deltaTime);
}

void CItem::MoveUpdate(float deltaTime)
{

	if (this->itemName == SmallHeart || this->itemName == LargeHeart)
	{
		if (this->m_Pos.y > 48) {
			this->m_Pos.y -= this->m_vyDefault * deltaTime;
			this->m_Pos.x = this->m_PosDefault.x + std::sin((this->m_Pos.y - this->m_PosDefault.y) / 50 * PI) * 30;
		}
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
