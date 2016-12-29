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
	//Init Animation
#pragma region MoneyBag Init 1
	switch (this->itemName)
	{
	case ITEM_name::MoneyBag:
		this->m_currentTime = 0;
		this->m_currentFrame = 0;
		this->m_elapseTimeChangeFrame = 0.1f;
		this->m_increase = 1;
		this->m_totalFrame = 3;
		this->m_column = 3;
		break;
	case ITEM_name::MoneyBagPoint:
	case ITEM_name::MoneyBagPointBlue:
	case ITEM_name::MoneyBagPointRed:
	case ITEM_name::MoneyBagPointWhite:
		this->m_currentTime = 0;
		this->m_currentFrame = 0;
		this->m_elapseTimeChangeFrame = 0.0f;
		this->m_increase = 0;
		this->m_totalFrame = 4;
		this->m_column = 1;
		break;
	default:
		break;
	}
#pragma endregion
	
	switch (this->itemName)
	{
	case ITEM_name::MoneyBagPoint:
		this->m_Width = 44;
		this->m_Height = 16;
		this->m_startFrame = 3;
		this->m_endFrame = 3;
		break;
	case ITEM_name::MoneyBagPointRed:
		this->m_Width = 44;
		this->m_Height = 16;
		this->m_startFrame = 0;
		this->m_endFrame = 0;
		break;
	case ITEM_name::MoneyBagPointWhite:
		this->m_Width = 44;
		this->m_Height = 16;
		this->m_startFrame = 2;
		this->m_endFrame = 2;
		break;
	case ITEM_name::MoneyBagPointBlue:
		this->m_Width = 44;
		this->m_Height = 16;
		this->m_startFrame = 1;
		this->m_endFrame = 1;
		break;
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
#pragma region MoneyBag Init 2
	case ITEM_name::MoneyBag:
		this->m_Width = 30;
		this->m_Height = 30;
		this->m_startFrame = 0;
		this->m_endFrame = 2;
		break;
	case ITEM_name::MoneyBagBlue:
	case ITEM_name::MoneyBagRed:
	case ITEM_name::MoneyBagWhite:
		this->m_Width = 30;
		this->m_Height = 30;
		break;
#pragma endregion
	case ITEM_name::Cross:
		this->m_Width = 32;
		this->m_Height = 32;
		break;
	//WEAPON ITEM
	case ITEM_name::Axe:
		this->m_Width = 30;
		this->m_Height = 28;
		break;
	case ITEM_name::Boomerang:
		this->m_Width = 30;
		this->m_Height = 28;
		break;
	case ITEM_name::FireBomb:
		this->m_Width = 32;
		this->m_Height = 32;
		break;
	case ITEM_name::Dagger:
		this->m_Width = 32;
		this->m_Height = 18;
		break;

	case ITEM_name::PorkChop:
		this->m_Width = 32;
		this->m_Height = 26;
		break;
		//BOSS ITEM
	case ITEM_name::MagicalCrystal:
		this->m_Width = 28;
		this->m_Height = 32;
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
	switch (this->itemName)
	{
	case ITEM_name::MoneyBag:
	case ITEM_name::MoneyBagBlue:
	case ITEM_name::MoneyBagRed:
	case ITEM_name::MoneyBagWhite:
		this->ChangeFrame(deltaTime);
		this->m_current_time_life += deltaTime;
		if (this->m_current_time_life >= 5.0f)
		{
			this->m_isRemove = true;
		}
		break;
	case ITEM_name::MoneyBagPoint:
	case ITEM_name::MoneyBagPointBlue:
	case ITEM_name::MoneyBagPointRed:
	case ITEM_name::MoneyBagPointWhite:
		this->ChangeFrame(deltaTime);
		this->m_current_time_life += deltaTime;
		if (this->m_current_time_life >= 1.0f)
		{
			this->m_isRemove = true;
		}
		break;
	default:
		this->m_current_time_life += deltaTime;
		if (this->m_current_time_life >= 5.0f)
		{
			this->m_isRemove = true;
		}
		break;
	}
	MoveUpdate(deltaTime);
}

void CItem::MoveUpdate(float deltaTime)
{

	switch (this->itemName)
	{
	case ITEM_name::SmallHeart:
	case ITEM_name::LargeHeart:
		this->m_Pos.y -= this->m_vyDefault * deltaTime;
		this->m_Pos.x = this->m_PosDefault.x + std::sin((this->m_Pos.y - this->m_PosDefault.y) / 50 * PI) * 30;
		break;
	case ITEM_name::MoneyBagPoint:
	case ITEM_name::MoneyBagPointBlue:
	case ITEM_name::MoneyBagPointRed:
	case ITEM_name::MoneyBagPointWhite:
		this->m_Pos.y += this->m_vyDefault * deltaTime;
		break;
	default:
		this->m_Pos.y -= this->m_vyDefault * deltaTime;
		break;
	}

	
}

Box CItem::GetBox()
{
	return Box(this->m_Pos.x, this->m_Pos.y, this->m_Width - 2, this->m_Height-2);
}

RECT * CItem::GetRectRS()
{
	RECT * rec = new RECT();
	switch (this->itemName)
	{
	case ITEM_name::MoneyBag:
	case ITEM_name::MoneyBagPoint:
	case ITEM_name::MoneyBagPointBlue:
	case ITEM_name::MoneyBagPointRed:
	case ITEM_name::MoneyBagPointWhite:
		return this->UpdateRectResource(m_Height, m_Width);
		break;
	default:
		rec->left = 0;
		rec->right = rec->left + m_Width;
		rec->top = 0;
		rec->bottom = rec->top + m_Height;
		
		break;
	}
	return rec;
}





CItem::~CItem()
{
}
