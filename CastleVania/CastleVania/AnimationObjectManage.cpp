#include "AnimationObjectManage.h"



CAnimationObjectManage::CAnimationObjectManage()
{
	
	
}


CAnimationObjectManage::~CAnimationObjectManage()
{
}

void CAnimationObjectManage::Update(float deltaTime)
{
	if (!this->m_listAnimationObject.empty())
	{
		for (std::vector<CAnimationObject*>::iterator it = this->m_listAnimationObject.begin();
			it != this->m_listAnimationObject.end(); ++it)
		{
			CAnimationObject* animationObj = *it;
			if (animationObj != NULL && animationObj->m_isRemove == false)
			{
				animationObj->Update(deltaTime);
			}
			if (animationObj->m_isRemove == true)
			{
				it = this->m_listAnimationObject.erase(it);
				break;
			}
		}
	}
}

CAnimationObject * CAnimationObjectManage::CreateAnimation(Animation_object animationType, Vector2 pos)
{
	CAnimationObject *obj;
	switch (animationType)
	{
	case Animation_object::FireOn:
		obj = new CFireOnAnimate(pos);
		break;
	case Animation_object::RockFall:
		obj = new CRockFallAnimate(pos);
		break;
	case Animation_object::BrickItemLv1:
		obj = new CBrickWithItem(pos);
		break;
	case Animation_object::BrickItemLv2:
		obj = new CBrickWithItemLv2(pos);
		break;
	case Animation_object::None:
		return nullptr;
		break;
	default:
		return nullptr;
		break;
	}
	this->m_listAnimationObject.push_back(obj);
	return obj;
}

CAnimationObject * CAnimationObjectManage::CreateAnimation(Animation_object animationType, Vector2 pos, ITEM_name itemName)
{
	CAnimationObject * obj = CreateAnimation(animationType, pos);
	obj->itemName = itemName;
	return obj;
}

void CAnimationObjectManage::DrawAnimationObject(CAnimationObject * animationObj)
{
	this->posDraw = CCamera::GetInstance()->GetPointTransform(animationObj->m_Pos.x, animationObj->m_Pos.y);
	switch (animationObj->m_typeAnimationObject)
	{
	case Animation_object::FireOn:
		this->Texture->LoadImageFromFile(ANIMATION_FIREON, D3DCOLOR_XRGB(255, 0, 255));
		break;
	case Animation_object::RockFall:
		this->Texture->LoadImageFromFile(ANIMATION_ROCKFALL, D3DCOLOR_XRGB(255, 0, 255));
		break;
	case Animation_object::BrickItemLv1:
		this->Texture->LoadImageFromFile(BRICK_LV1, D3DCOLOR_XRGB(255, 0, 255));
		break;
	case Animation_object::BrickItemLv2:
		this->Texture->LoadImageFromFile(BRICK_LV2, D3DCOLOR_XRGB(255, 0, 255));
		break;
	case Animation_object::None:
		return;
		break;
	default:
		return;
		break;
	}
	switch (animationObj->m_DrawFlip)
	{
	case DrawFlip::NONE:
		this->m_draw->Draw(this->Texture, animationObj->GetRectRS(), this->posDraw, D3DCOLOR_XRGB(255, 255, 255), true);
		break;
	case DrawFlip::X:
		this->m_draw->DrawFlipX(this->Texture, animationObj->GetRectRS(), this->posDraw, D3DCOLOR_XRGB(255, 255, 255), true);
		break;
	case DrawFlip::Y:
		this->m_draw->DrawFlipY(this->Texture, animationObj->GetRectRS(), this->posDraw, D3DCOLOR_XRGB(255, 255, 255), true);
		break;
	case DrawFlip::XY:
		this->m_draw->DrawFlipXY(this->Texture, animationObj->GetRectRS(), this->posDraw, D3DCOLOR_XRGB(255, 255, 255), true);
		break;
	default:
		this->m_draw->Draw(this->Texture, animationObj->GetRectRS(), this->posDraw, D3DCOLOR_XRGB(255, 255, 255), true);
		break;
	}
}

void CAnimationObjectManage::CreateAnimationObject(int lv)
{
	if (lv == 2)
	{
		this->CreateAnimation(Animation_object::RockFall, Vector2(3598, 126))->m_DrawFlip = DrawFlip::NONE;
		this->CreateAnimation(Animation_object::RockFall, Vector2(3598, 110))->m_DrawFlip = DrawFlip::NONE;
		this->CreateAnimation(Animation_object::RockFall, Vector2(3598, 78), ITEM_name::PorkChop)->m_DrawFlip = DrawFlip::NONE;
		
		//this->CreateAnimation(Animation_object::BrickItemLv2, Vector2(250, 90), ITEM_name::Axe);
	}
	if (lv == 4)
	{
		this->CreateAnimation(Animation_object::BrickItemLv1, Vector2(1904, 105), ITEM_name::PorkChop)->m_DrawFlip = DrawFlip::X;
	}
	if (lv == 6)
	{
		this->CreateAnimation(Animation_object::BrickItemLv2, Vector2(2258,207), ITEM_name::Axe);
	}
	if (lv == 7)
	{
		this->CreateAnimation(Animation_object::BrickItemLv2, Vector2(1423, 142), ITEM_name::PorkChop);
		this->CreateAnimation(Animation_object::BrickItemLv2, Vector2(274, 109), ITEM_name::Axe);
	}
}

void CAnimationObjectManage::Draw()
{
	if (!this->m_listAnimationObject.empty())
	{
		for (std::vector<CAnimationObject*>::iterator it = this->m_listAnimationObject.begin();
			it != this->m_listAnimationObject.end(); ++it)
		{
			CAnimationObject * obj = *it;
			this->DrawAnimationObject(obj);
		}
	}
}
