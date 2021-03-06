﻿#include "DrawObject.h"

CDrawObject::CDrawObject()
{
}


CDrawObject::~CDrawObject()
{
}

void CDrawObject::Draw(CBaseGameObject *obj)// quan li viec load va ve cac doi tuong tai cac vi tri xac dinh
{
	//Kiem tra doi tuong khac null
	if (obj != nullptr)
	{
		int id = obj->GetID();
		CTexture* texture = new CTexture();
		Vector3 pos = Vector3();
		RECT* rectRS1 = new RECT();
		pos = CCamera::GetInstance()->GetPointTransform(obj->GetPos().x, obj->GetPos().y);

		switch (id)
		{
		case 2:

			texture->LoadImageFromFile("..\\Resources\\image\\enemy\\AxeMan.png", D3DCOLOR_XRGB(255, 255, 255));
			

			//cập nhật lại vị trí của Rect Resource
			rectRS1->left = 0;
			rectRS1->right = obj->m_Width;
			rectRS1->top = 0;
			rectRS1->bottom = obj->m_Height;
			this->m_draw->Draw(texture, rectRS1, pos, D3DCOLOR_XRGB(255, 255, 255), true);
			break;

		case 3:
			texture->LoadImageFromFile(HV2, D3DCOLOR_XRGB(255, 255, 255));
			this->m_draw->Draw(texture, obj->GetRectRS(), pos, D3DCOLOR_XRGB(255, 255, 255), true);
			break;

		case 601:
			texture->LoadImageFromFile(GROUND, D3DCOLOR_XRGB(255, 0, 255));
			this->m_draw->Draw(texture, obj->GetRectRS(), pos, D3DCOLOR_XRGB(255, 255, 255), true);
			break;

		case 301:
			texture->LoadImageFromFile(ITEM_SMALL_HEART, D3DCOLOR_XRGB(255, 0, 255));
			this->m_draw->Draw(texture, obj->GetRectRS(), pos, D3DCOLOR_XRGB(255, 255, 255), true);
			break;

		case 302:
			texture->LoadImageFromFile(ITEM_LARGE_HEART, D3DCOLOR_XRGB(255, 255, 255));
			this->m_draw->Draw(texture, obj->GetRectRS(), pos, D3DCOLOR_XRGB(255, 255, 255), true);
			break;

		case 310:
			texture->LoadImageFromFile(ITEM_MORNING_STAR, D3DCOLOR_XRGB(255, 0, 255));
			this->m_draw->Draw(texture, obj->GetRectRS(), pos, D3DCOLOR_XRGB(255, 255, 255), true);
			break;

		case 312:
			texture->LoadImageFromFile(ITEM_DAGGER, D3DCOLOR_XRGB(255, 255, 255));
			this->m_draw->Draw(texture, obj->GetRectRS(), pos, D3DCOLOR_XRGB(255, 255, 255), true);
			break;
		/*case 702:
			texture->LoadImageFromFile(BRICK, D3DCOLOR_XRGB(255, 255, 255));
			this->m_draw->Draw(texture, obj->GetRectRS(), pos, D3DCOLOR_XRGB(255, 255, 255), true);
			break;*/
		case 201:
			texture->LoadImageFromFile(ENEMY_ZOMBIE, D3DCOLOR_XRGB(255, 0, 255));
			if (obj->m_Dir == LEFT)
			{
				this->m_draw->Draw(texture, obj->GetRectRS(), pos, D3DCOLOR_XRGB(255, 255, 255), true);
			}
			else
			{
				this->m_draw->DrawFlipX(texture, obj->GetRectRS(), pos, D3DCOLOR_XRGB(255, 255, 255), true);
			}
			break;
		case 208:
			texture->LoadImageFromFile(ENEMY_BLACKKNIGHT, D3DCOLOR_XRGB(255, 0, 255));
			if (obj->m_Dir == LEFT)
			{
				this->m_draw->Draw(texture, obj->GetRectRS(), pos, D3DCOLOR_XRGB(255, 255, 255), true);
			}
			else
			{
				this->m_draw->DrawFlipX(texture, obj->GetRectRS(), pos, D3DCOLOR_XRGB(255, 255, 255), true);
			}
			break;
		case 207:
			texture->LoadImageFromFile(ENEMY_DRAGON_SKULL, D3DCOLOR_XRGB(255, 0, 255));
			if (obj->m_Dir == RIGHT)
			{
				this->m_draw->Draw(texture, obj->GetRectRS(), pos, D3DCOLOR_XRGB(255, 255, 255), true);
			}
			else
			{
				this->m_draw->DrawFlipX(texture, obj->GetRectRS(), pos, D3DCOLOR_XRGB(255, 255, 255), true);
			}
			break;
		case 600:
			texture->LoadImageFromFile(OBJECT_SMALLLIGHT, D3DCOLOR_XRGB(255, 0, 255));
			this->m_draw->Draw(texture, obj->GetRectRS(), pos, D3DCOLOR_XRGB(255, 255, 255), true);
			break;
		case 401:
			texture->LoadImageFromFile(BOSS_VAMPIREBAT, D3DCOLOR_XRGB(255, 0, 255));
			this->m_draw->Draw(texture, obj->GetRectRS(), pos, D3DCOLOR_XRGB(255, 255, 255), true);
			break;
		case 202:
			texture->LoadImageFromFile(ENEMY_BLACKLEOPARD, D3DCOLOR_XRGB(255, 0, 255));
			this->m_draw->Draw(texture, obj->GetRectRS(), pos, D3DCOLOR_XRGB(255, 255, 255), true);
			break;
		case 205:
			texture->LoadImageFromFile(ENEMY_FISHMAN, D3DCOLOR_XRGB(255, 0, 255));
			if (obj->m_Dir == LEFT)
			{
				this->m_draw->Draw(texture, obj->GetRectRS(), pos, D3DCOLOR_XRGB(255, 255, 255), true);
			}
			else
			{
				this->m_draw->DrawFlipX(texture, obj->GetRectRS(), pos, D3DCOLOR_XRGB(255, 255, 255), true);
			}
			break;
		case 204:
			texture->LoadImageFromFile(ENEMY_MEDUSA, D3DCOLOR_XRGB(255, 0, 255));
			this->m_draw->DrawFlipX(texture, obj->GetRectRS(), pos, D3DCOLOR_XRGB(255, 255, 255), true);
			break;
		case 203:
			texture->LoadImageFromFile(ENEMY_VAMPIREBAT, D3DCOLOR_XRGB(255, 0, 255));
			this->m_draw->Draw(texture, obj->GetRectRS(), pos, D3DCOLOR_XRGB(255, 255, 255), true);
			break;
		case 653:
			texture->LoadImageFromFile(GROUND_MOVING_PLATFORM, D3DCOLOR_XRGB(255, 0, 255));
			this->m_draw->Draw(texture, obj->GetRectRS(), pos, D3DCOLOR_XRGB(255, 255, 255), true);
			break;
		case 402:
			texture->LoadImageFromFile(BOSS_MEDUSA, D3DCOLOR_XRGB(255, 0, 255));
			this->m_draw->Draw(texture, obj->GetRectRS(), pos, D3DCOLOR_XRGB(255, 255, 255), true);
			break;
			
		}
	}
}

void CDrawObject::Draw(CBaseGameObject *object, D3DCOLOR color)
{
}
