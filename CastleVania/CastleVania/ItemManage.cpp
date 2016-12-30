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
	/*this->CreateItem(ITEM_name::MoneyBagPoint, this->simon->m_Pos);*/
}

void CItemManage::Update(float deltaTime)
{
	CItemManage::OnSimonCollision(deltaTime);
	if (!this->m_ListItem.empty())
	{
		for (std::vector<CItem*>::iterator em = m_ListItem.begin(); em != m_ListItem.end(); ++em)
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
		for (std::vector<CItem*>::iterator em = m_ListItem.begin(); em != m_ListItem.end(); ++em)
		{
			CItem* Item = *em;
			if (Item->itemName == ITEM_name::MoneyBagPoint)
			{
				int a = 1;
			}
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
	case ITEM_name::MoneyBagRed:
		texture->LoadImageFromFile(ITEM_MONEY_BAG_RED, D3DCOLOR_XRGB(255, 0, 255));
		break;
	case ITEM_name::MoneyBagWhite:
		texture->LoadImageFromFile(ITEM_MONEY_BAG_WHITE, D3DCOLOR_XRGB(255, 0, 255));
		break;
	case ITEM_name::MoneyBagBlue:
		texture->LoadImageFromFile(ITEM_MONEY_BAG_BLUE, D3DCOLOR_XRGB(255, 0, 255));
		break;
	case ITEM_name::MoneyBagPoint:
	case ITEM_name::MoneyBagPointRed:
	case ITEM_name::MoneyBagPointWhite:
	case ITEM_name::MoneyBagPointBlue:
		texture->LoadImageFromFile(ITEM_MONEY_BAG_POINT, D3DCOLOR_XRGB(255, 0, 255));
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
	case ITEM_name::MagicalCrystal:
		texture->LoadImageFromFile(ITEM_MAGICALCRYSTAL, D3DCOLOR_XRGB(255, 0, 255));
		break;

	}

	this->m_draw->Draw(texture, obj->GetRectRS(), pos, D3DCOLOR_XRGB(255, 255, 255), true);
}

void CItemManage::OnSimonCollision(float deltaTime)
{
	if (this->m_ListItem.size() != 0)
	{
		for (std::vector<CItem*>::iterator it = this->m_ListItem.begin();
			it != this->m_ListItem.end();
			++it)
		{
			CItem* item = *it;
			
			if (COnCollision::GetInstance()->AABBCheck(simon->GetBox(), item->GetBox()))
			{
				//ManageAudio::GetInstance()->playSound(TypeAudio::Collect_Item);
				switch (item->itemName)
				{
				case ITEM_name::Axe:
					simon->m_currentWeapon = WEAPON_name::Axe;
					ManageAudio::GetInstance()->playSound(TypeAudio::CollectWeapon);
					break;
				case ITEM_name::Boomerang:
					simon->m_currentWeapon = WEAPON_name::Boomerang;
					ManageAudio::GetInstance()->playSound(TypeAudio::CollectWeapon);
					break;
				case ITEM_name::FireBomb:
					simon->m_currentWeapon = WEAPON_name::FireBomb;
					ManageAudio::GetInstance()->playSound(TypeAudio::CollectWeapon);
					break;
				case ITEM_name::Dagger:
					simon->m_currentWeapon = WEAPON_name::Dagger;
					ManageAudio::GetInstance()->playSound(TypeAudio::CollectWeapon);
					break;
				case ITEM_name::MorningStar:
					this->simon->isPickUpMorningStar = true;
					ManageAudio::GetInstance()->playSound(TypeAudio::Collect_Item);
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
						else
						{
							break;
						}
					}
					break;
				case ITEM_name::PorkChop:
					ManageAudio::GetInstance()->playSound(TypeAudio::Collect_Item);
					break;
				case ITEM_name::Cross:
					ManageAudio::GetInstance()->playSound(TypeAudio::Collect_Item);
					break;
				case ITEM_name::LargeHeart:
					ManageAudio::GetInstance()->playSound(TypeAudio::Collect_Item);
					simon->m_countHeart += 5;
					break;
				case ITEM_name::SmallHeart:
					ManageAudio::GetInstance()->playSound(TypeAudio::Collect_Item);
					simon->m_countHeart += 1;
					break;
				case ITEM_name::MoneyBagBlue:
					this->simon->m_Score += 400;
					ManageAudio::GetInstance()->playSound(TypeAudio::Collect_Item);
					this->m_ListItem.erase(it);//xoa item khoi list khi cham vao simon
					this->CreateItem(ITEM_name::MoneyBagPointBlue, item->m_Pos);
					return;
					break;
				case ITEM_name::MoneyBagWhite:
					this->simon->m_Score += 700;
					this->CreateItem(ITEM_name::MoneyBagPointWhite, item->m_Pos);
					ManageAudio::GetInstance()->playSound(TypeAudio::Collect_Item);
					break;
				case ITEM_name::MoneyBagRed:
					this->simon->m_Score += 100;
					this->CreateItem(ITEM_name::MoneyBagPointRed, item->m_Pos);
					ManageAudio::GetInstance()->playSound(TypeAudio::Collect_Item);
					break;
				case ITEM_name::MoneyBag:
					this->m_ListItem.erase(it);//xoa item khoi list khi cham vao simon
					this->CreateItem(ITEM_name::MoneyBagPoint, item->m_Pos);
					ManageAudio::GetInstance()->playSound(TypeAudio::Collect_Item);
					this->simon->m_Score += 1000;
					return;
					break;
				case ITEM_name::MagicalCrystal:
					this->m_ListItem.erase(it);//xoa item khoi list khi cham vao simon
					ManageAudio::GetInstance()->playSound(TypeAudio::Collect_Item);
					this->simon->m_hpSimon = 16;
					this->simon->m_Score += 2000;
					return;
					break;
				default:
					return;
					break;
				}
				//Chi xoa item khi no ko phai la point
				switch (item->itemName)
				{
				case ITEM_name::MoneyBagPoint:
				case ITEM_name::MoneyBagPointBlue:
				case ITEM_name::MoneyBagPointRed:
				case ITEM_name::MoneyBagPointWhite:
					return;
					break;
				default:
					it = this->m_ListItem.erase(it);
					return;
					break;
				}
			}
			/*}*/
		}
	}
}

