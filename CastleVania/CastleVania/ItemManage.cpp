#include "ItemManage.h"
#include "Resources.h"
#include "Simon.h"
#include "OnCollision.h"
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
	int item_id_arr[8] = { 301,302,305,309,310,312,315,316 };
	int item_index = rand() % 8;
	ITEM_name name = static_cast<ITEM_name>(item_id_arr[item_index]);
	this->CreateItem(name, Vector2(pos.x,pos.y));
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

	case SmallHeart:
		texture->LoadImageFromFile(ITEM_SMALL_HEART, D3DCOLOR_XRGB(255, 255, 255));
		break;

	case LargeHeart:
		texture->LoadImageFromFile(ITEM_LARGE_HEART, D3DCOLOR_XRGB(255, 255, 255));
		break;

	case MoneyBag:
		texture->LoadImageFromFile(ITEM_MONEY_BAG, D3DCOLOR_XRGB(255, 255, 255));
		break;

	case MorningStar:
		texture->LoadImageFromFile(ITEM_MORNING_STAR, D3DCOLOR_XRGB(255, 255, 255));
		break;

	case Dagger:
		texture->LoadImageFromFile(ITEM_DAGGER, D3DCOLOR_XRGB(255, 255, 255));
		break;

	case Axe:
		texture->LoadImageFromFile(ITEM_AXE, D3DCOLOR_XRGB(255, 255, 255));
		break;

	case Cross:
		texture->LoadImageFromFile(ITEM_CROSS, D3DCOLOR_XRGB(255, 255, 255));
		break;
	case PorkChop:
		texture->LoadImageFromFile(ITEM_PORK_CHOP, D3DCOLOR_XRGB(255, 255, 255));
		break;

	}

	this->m_draw->Draw(texture, obj->GetRectRS(), pos, D3DCOLOR_XRGB(255, 255, 255), true);
}

void CItemManage::OnSimonCollision(float deltaTime)
{
	if (this->m_ListItem.size()!=0)
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
				if (COnCollision::GetInstance()->AABBCheck(simon->GetBox(),item->GetBox()))
				{
					this->m_ListItem.erase(it);
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

