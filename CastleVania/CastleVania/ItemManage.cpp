#include "ItemManage.h"
CItemManage::CItemManage()
{
	Init();
}


CItemManage::~CItemManage()
{
}

void CItemManage::Init()
{

}

void CItemManage::Update(float deltaTime)
{
	CItemManage::OnSimonCollision(deltaTime);
	if (!this->m_ListItem.empty())
	{
		for (std::list<CItem*>::iterator em = m_ListItem.begin(); em != m_ListItem.end(); ++em)
		{
			CItem* Item = *em;
			Item->Update(deltaTime);
			if (Item->m_isRemove)
			{
				m_ListItem.erase(em);
				break;
			}
		}
	}
}

void CItemManage::CreateItem(ITEM_name itemName, Vector2 pos)
{
	CItem* Item = new CItem(itemName, pos);
	this->m_ListItem.push_back(Item);

}

void CItemManage::CreateRandomItem(Vector2 pos)
{
	ITEM_name item_name_arr[10] = {
		ITEM_name::SmallHeart,
		ITEM_name::LargeHeart,
		ITEM_name::Axe,
		ITEM_name::Boomerang,
		ITEM_name::FireBomb,
		ITEM_name::Dagger,
		ITEM_name::PorkChop,
		ITEM_name::Cross,
		ITEM_name::MoneyBag,
		ITEM_name::MorningStar
	};
	int item_index = rand() % 10;
	this->CreateItem(item_name_arr[item_index], Vector2(pos.x, pos.y));
}

void CItemManage::Draw()
{

	if (!this->m_ListItem.empty())
	{
		for (std::list<CItem*>::iterator em = m_ListItem.begin(); em != m_ListItem.end(); ++em)
		{
			CItem* Item = *em;
			this->DrawItem(Item);
		}
	}
}

void CItemManage::DrawItem(CItem * obj)
{
	int id = obj->GetID();
	ITEM_name itemName = obj->itemName;
	CTexture* texture = new CTexture();
	Vector3 pos = Vector3();
	pos = CCamera::GetInstance()->GetPointTransform(obj->GetPos().x, obj->GetPos().y);
	switch (itemName)
	{

	case ITEM_name::SmallHeart:
		texture->LoadImageFromFile(ITEM_SMALL_HEART, D3DCOLOR_XRGB(255, 0, 255));
		break;

	case ITEM_name::LargeHeart:
		texture->LoadImageFromFile(ITEM_LARGE_HEART, D3DCOLOR_XRGB(255, 0, 255));
		break;

	case ITEM_name::MoneyBag:
		texture->LoadImageFromFile(ITEM_MONEY_BAG, D3DCOLOR_XRGB(255, 0, 255));
		break;

	case ITEM_name::MorningStar:
		texture->LoadImageFromFile(ITEM_MORNING_STAR, D3DCOLOR_XRGB(255, 0, 255));
		break;
		//item weapon
	case ITEM_name::Dagger:
		texture->LoadImageFromFile(ITEM_DAGGER, D3DCOLOR_XRGB(255, 0, 255));
		break;
	case ITEM_name::Axe:
		texture->LoadImageFromFile(ITEM_AXE, D3DCOLOR_XRGB(255, 0, 255));
		break;
	case ITEM_name::Boomerang:
		texture->LoadImageFromFile(ITEM_BOOMERANG, D3DCOLOR_XRGB(255, 0, 255));
		break;
	case ITEM_name::FireBomb:
		texture->LoadImageFromFile(ITEM_FIREBOMB, D3DCOLOR_XRGB(255, 0, 255));
		break;

	case ITEM_name::Cross:
		texture->LoadImageFromFile(ITEM_CROSS, D3DCOLOR_XRGB(255, 0, 255));
		break;
	case ITEM_name::PorkChop:
		texture->LoadImageFromFile(ITEM_PORK_CHOP, D3DCOLOR_XRGB(255, 0, 255));
		break;

	}

	this->m_draw->Draw(texture, obj->GetRectRS(), pos, D3DCOLOR_XRGB(255, 255, 255), true);
}

void CItemManage::OnSimonCollision(float deltaTime)
{
	if (this->m_ListItem.size() != 0)
	{
		CSimon* simon = CSimon::GetInstance();
		for (std::list<CItem*>::iterator it = this->m_ListItem.begin();
			it != this->m_ListItem.end();
			++it)
		{
			CItem* item = *it;
			/*if (item->m_Id == 301 || item->m_Id == 302 || item->m_Id == 310 || item->m_Id == 312)
			{*/
			/*CDirection normalX;
			CDirection normalY;
			float timeCollision;
			timeCollision = COnCollision::GetInstance()->SweepAABB(simon, item, normalX, normalX, deltaTime);
			if (normalX == CDirection::ON_LEFT || normalX == CDirection::ON_RIGHT)
			{*/
			if (COnCollision::GetInstance()->AABBCheck(simon->GetBox(), item->GetBox()))
			{
				switch (item->itemName)
				{
				case ITEM_name::Axe:
					simon->m_currentWeapon = WEAPON_name::Axe;
					break;
				case ITEM_name::Boomerang:
					simon->m_currentWeapon = WEAPON_name::Boomerang;
					break;
				case ITEM_name::FireBomb:
					simon->m_currentWeapon = WEAPON_name::FireBomb2;
					break;
				case ITEM_name::Dagger:
					simon->m_currentWeapon = WEAPON_name::Dagger;
					break;
				default:
					break;
				}
				this->m_ListItem.erase(it);//xoa item khoi list khi cham vao simon
				if (simon->cane->m_State == caneState::default)
				{
					simon->cane->updateState(state2);
				}
				else
				{
					if (simon->cane->m_State == state2)
					{
						simon->cane->updateState(state3);
					}
				}
				break;
			}
			/*}*/
		}
	}
}

