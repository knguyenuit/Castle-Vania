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
}

void CItemManage::CreateItem(ITEM_name itemName, Vector2 pos)
{
	CItem* Item = new CItem(itemName, pos);
	this->m_ListItem.push_back(Item);

}

void CItemManage::CreateRandomItem(Vector2 pos)
{
	int item_id_arr[4] = { 301,302,310,312 };
	int item_index = rand() % 4;
	ITEM_name name = static_cast<ITEM_name>(item_id_arr[item_index]);
	this->CreateItem(name, pos);
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
	CTexture* texture = new CTexture();
	Vector3 pos = Vector3();
	pos = CCamera::GetInstance()->GetPointTransform(obj->GetPos().x, obj->GetPos().y);
	switch (id)
	{

	case 301:
		texture->LoadImageFromFile(ITEM_SMALL_HEART, D3DCOLOR_XRGB(255, 255, 255));
		this->m_draw->Draw(texture, obj->GetRectRS(), pos, D3DCOLOR_XRGB(255, 255, 255), true);
		break;

	case 302:
		texture->LoadImageFromFile(ITEM_LARGE_HEART, D3DCOLOR_XRGB(255, 255, 255));
		this->m_draw->Draw(texture, obj->GetRectRS(), pos, D3DCOLOR_XRGB(255, 255, 255), true);
		break;

	case 310:
		texture->LoadImageFromFile(ITEM_MORNING_STAR, D3DCOLOR_XRGB(255, 255, 255));
		this->m_draw->Draw(texture, obj->GetRectRS(), pos, D3DCOLOR_XRGB(255, 255, 255), true);
		break;

	case 312:
		texture->LoadImageFromFile(ITEM_DAGGER, D3DCOLOR_XRGB(255, 255, 255));
		this->m_draw->Draw(texture, obj->GetRectRS(), pos, D3DCOLOR_XRGB(255, 255, 255), true);
		break;
	}
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
			if (item->m_Id == 301 || item->m_Id == 302 || item->m_Id == 310 || item->m_Id == 312)
			{
				if (COnCollision::GetInstance()->AABBCheck(simon->GetBox(), item->GetBox()))
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
			}
		}
	}
}


