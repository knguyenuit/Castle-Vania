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
	/*for (std::vector<CItem*>::iterator em = this->m_ListItem.begin(); em !=this->m_ListItem.end(); ++em)
	{
		CItem* Item = *em;
		DrawItem(Item);
	}*/
	/*if (this->m_ListItem.size()!=0)
	{
		DrawItem(this->m_ListItem.at(0));
	}*/

	
}

CItem* CItemManage::CreateItem(ITEM_name itemName, Vector2 pos)
{
	CItem* Item = new CItem(itemName, pos);
	return Item;
	//this->m_ListItem.push_back(Item);
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
		texture->LoadImageFromFile(ITEM_SMALL_HEART, D3DCOLOR_XRGB(255, 0, 255));
		this->m_draw->Draw(texture, obj->GetRectRS(), pos, D3DCOLOR_XRGB(255, 255, 255), true);
		break;

	case 302:
		texture->LoadImageFromFile(ITEM_LARGE_HEART, D3DCOLOR_XRGB(255, 0, 255));
		this->m_draw->Draw(texture, obj->GetRectRS(), pos, D3DCOLOR_XRGB(255, 255, 255), true);
		break;

	case 310:
		texture->LoadImageFromFile(ITEM_MORNING_STAR, D3DCOLOR_XRGB(255, 0, 255));
		this->m_draw->Draw(texture, obj->GetRectRS(), pos, D3DCOLOR_XRGB(255, 255, 255), true);
		break;

	case 312:
		texture->LoadImageFromFile(ITEM_DAGGER, D3DCOLOR_XRGB(255, 0, 255));
		this->m_draw->Draw(texture, obj->GetRectRS(), pos, D3DCOLOR_XRGB(255, 255, 255), true);
		break;
	}
}


