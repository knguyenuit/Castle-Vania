#include "ItemManage.h"
#include "Resources.h"

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

	if (!this->m_ListItem.empty())
	{
		for (std::vector<CItem*>::iterator em = this->m_ListItem.begin(); em != this->m_ListItem.end(); ++em)
		{
			CItem* gameObj = *em;
			if (gameObj != NULL && gameObj->m_isRemove == false)
			{
				gameObj->Update(deltaTime);
			}
			
			if (gameObj->m_isRemove)
			{
				em = this->m_ListItem.erase(em);
				if (m_ListItem.empty())
				{
					break;
				}
			}
		}
	}

}

void CItemManage::CreateItem(ITEM_name itemName, Vector2 pos)
{
	CItem* Item = new CItem(itemName, pos);
	this->m_ListItem.push_back(Item);
	isAdd = false;

}

void CItemManage::CreateRandomItem(Vector2 pos)
{
	int item_id_arr[4] = { 301,302,310,312 };
	int item_index = rand() % 4;
	ITEM_name name = static_cast<ITEM_name>(item_id_arr[item_index]);
	if (isAdd)
	{
		this->CreateItem(name, pos);
	}
}

void CItemManage::Draw()
{

	if (this->m_ListItem.size() != 0)
	{
		for (std::vector<CItem*>::iterator em = this->m_ListItem.begin(); em != this->m_ListItem.end(); ++em)
		{
			CItem* Item = *em;
			if (Item->m_IsActive)
			{
				this->DrawItem(Item);

				break;
			}

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


