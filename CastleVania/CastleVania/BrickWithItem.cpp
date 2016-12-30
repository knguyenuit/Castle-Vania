#include "BrickWithItem.h"

CBrickWithItem::CBrickWithItem()
{
	this->Init();
}

CBrickWithItem::CBrickWithItem(Vector2 pos)
{
	this->m_typeAnimationObject = Animation_object::BrickItemLv1;
	this->m_Pos = pos;
	this->itemName = itemName;
	this->Init();
}


CBrickWithItem::~CBrickWithItem()
{
}

void CBrickWithItem::Init()
{
	this->m_Width = this->m_Height = 32;
}

void CBrickWithItem::Update(float deltaTime)
{
	if (this->simon->cane->m_checkActive == true &&
		(this->simon->cane->m_currentFrame == 2 || this->simon->cane->m_currentFrame == 6 || this->simon->cane->m_currentFrame == 10))
	{
		this->OnCaneCollision(deltaTime);
	}
	this->OnSimonCollision(deltaTime);
	if (this->isCaneCollision == true)
	{
		ManageAudio::GetInstance()->playSound(TypeAudio::Hit);
		if (this->itemName != ITEM_name::None)
		{
			CItemManage::GetInstance()->CreateItem(this->itemName, this->m_Pos);
		}
		this->isCaneCollision = false;
		this->m_isRemove = true;
	}
}

void CBrickWithItem::OnCaneCollision(float deltaTime)
{
	if (CCollision::GetInstance()->AABBCheck(this->simon->cane->GetBox(), this->GetBox()))
	{
		this->isCaneCollision = true;
	}
}

void CBrickWithItem::OnSimonCollision(float deltaTime)
{
	//if (this->simon->simon_Status != SIMON_status::ONSTAIR)
	//{
	//	CDirection normalX;
	//	CDirection normalY;
	//	float timeCollision;
	//	timeCollision = COnCollision::GetInstance()->SweepAABB(this->simon->GetBox(), this->GetBox(), normalX, normalY, deltaTime);
	//	if (normalY == CDirection::ON_DOWN && this->simon->isOnStair == false && this->simon->isMoveToStair == false && this->simon->isCollisionEnemy == false)
	//	{
	//		simon->m_Pos.y = this->m_Pos.y + this->m_Height / 2 + simon->m_Height / 2 - 8;
	//		this->simon->simon_Status = SIMON_status::IDLE;
	//		this->simon->isKey_X = false;
	//		/*this->simon->isMoveJump = false;*/
	//	}
	//	if ((normalX == CDirection::ON_LEFT || normalX == CDirection::ON_RIGHT) && this->simon->isMoveJump == true)
	//	{
	//		this->simon->m_vx = 0;
	//	}
	//	if (this->simon->isCollisionEnemy == false)
	//	{
	//		if (this->simon->isMoveToStair == false && this->simon->isOnStair == false && this->simon->isDownStair == false && this->simon->prepareOnStair == false && this->simon->isJump == false)
	//		{
	//			if (this->simon->m_Pos.y > this->m_Pos.y)
	//			{
	//				if (COnCollision::GetInstance()->AABBCheck(this->simon->GetBox(), this->GetBox()))
	//				{

	//					if (this->simon->isSit == true && (this->simon->m_currentFrame == 4 || this->simon->m_currentFrame == 15 || this->simon->m_currentFrame == 16 || this->simon->m_currentFrame == 17))
	//					{
	//						simon->m_Pos.y = this->m_Pos.y + this->m_Height / 2 + simon->m_Height / 2 - 24;
	//					}
	//					else
	//					{
	//						simon->m_Pos.y = this->m_Pos.y + this->m_Height / 2 + simon->m_Height / 2 - 8;
	//					}
	//				}
	//			}

	//		}
	//	}

	//}
}

RECT * CBrickWithItem::GetRectRS()
{
	RECT * rec = new RECT();
	rec->left = 0;
	rec->right = rec->left + m_Width;
	rec->top = 0;
	rec->bottom = rec->top + m_Height;
	return rec;
}
